# Standalone TCJ + GUS core

Part of the **Gerarion** reference suite (verared/gerarion `v3.3.0`,
Gerarion Universal Standard). This directory is an **export package**
ready to be published (or consumed) as the `verared/gt-core` satellite
repository; it keeps the base repository's relative layout so modules
compose cleanly.

## The unique problem it solves

The minimum normative core: AY/DY calendar with Great Tempalum, canonical 32/29-character format, quick_verify, and int64 + nanos instants. Fit for microcontrollers and bare metal: no malloc, no OS clock, no TAI−UTC table, no dependencies.

## Normative status

- **Estable** (`maturity: stable`) — baseline `v3.3.0` (frozen arithmetic and vectors:
  GUS v3.0.0).
- Included specification(s): `docs/specs/TCJ.es.md`, `docs/specs/TCJ.en.md`, `docs/specs/GUS.es.md`, `docs/specs/GUS.en.md`
- Verifiable integrity manifest: [`EXPORT-MANIFEST.json`](EXPORT-MANIFEST.json)
- Official compatibility matrix: [`COMPATIBILITY.md`](https://github.com/verared/gerarion/blob/v3.3.0/COMPATIBILITY.md)

## Integrate `gt-core` + `gt-gst` in 1 Minute (CMS / API Quickstart)

```python
import hashlib
from gerarion.core import format as fmt
from gerarion.gst import HybridSigner, v2

# 1. Initialize hybrid signer (Ed25519 + ML-DSA-65), key trust registry, and SQLite ReplayStore
signer = HybridSigner(seed_classical=bytes(range(32)), seed_pqc=bytes(range(32, 64)))
registry = v2.KeyRegistry()
registry.register_signer(issuer="cms.example.org", kid="cms-2026-k1", signer=signer)
replay_store = v2.SQLiteReplayStore(":memory:")  # In production: "/var/lib/cms/gst_replay.sqlite3"

# 2. Seal a business event on a canonical GUS coordinate
event_bytes = b'{"action":"post.publish","object_id":"art-42","version":1}'
event_hash = "sha256:" + hashlib.sha256(event_bytes).hexdigest()
envelope = v2.create(
    fmt.parse("2031DY-03-08-T-09:30:00-SC-TCJ+0"),
    signer,
    event_hash=event_hash,
    issuer="cms.example.org",
    kid="cms-2026-k1",
    seq=1,
)

# 3. Verify across 3 independent levels (Cryptography, Identity/Replay, Temporal Assurance)
res = v2.verify(envelope, trust_store=registry, replay_store=replay_store)
assert res.crypto.valid is True
assert res.identity.valid is True and res.identity.key_status == "ACTIVE"
assert res.identity.replay_status == "OK"
assert res.temporal.clock_state == "UNKNOWN"  # Or "VERIFIED" when passing a gt-gts ClockReading
assert res.overall_trusted is True
```

## The 5 Distribution Guarantees

| # | Guarantee | Verifiable mechanism |
|---|---|---|
| 1 | **SHA-256 Integrity** | `files` map in [`EXPORT-MANIFEST.json`](EXPORT-MANIFEST.json) checked via `--verify-existing`. |
| 2 | **Declared Provenance** | `source_repo`, `source_tag` (`v3.3.0`), and 40-char `source_commit` fields. |
| 3 | **Publication Authenticity** | Detached Ed25519 signature `EXPORT-MANIFEST.json.sig` verified via `--trusted-pub-key` (zero self-reference). |
| 4 | **Reproducibility** | Bit-for-bit deterministic re-export from the same `--source-commit`. |
| 5 | **Functional Conformance** | Shared CC0 normative vectors and cross-satellite integration tests in C11, Python, and JavaScript. |

## Dependencies

- **None: 100 % standalone.** May be adopted independently from the rest of the suite.

## Contents

- `EXPORT-MANIFEST.json`
- `LICENSE`
- `NOTICE`
- `docs/specs/GUS.en.md`
- `docs/specs/GUS.es.md`
- `docs/specs/TCJ.en.md`
- `docs/specs/TCJ.es.md`
- `impl-c/Makefile`
- `impl-c/gerarion-core.pc.in`
- `impl-c/smoke.c`
- `impl-c/core/gus_core.c`
- `impl-c/core/gus_core.h`
- `src/gerarion/core/__init__.py`
- `src/gerarion/core/calendar.py`
- `src/gerarion/core/format.py`
- `vectors/gus-normative-003.json`
- `vectors/gus-quickverify-001.json`
- `vectors/gus-regression-001.json`
- `web/engine/core.mjs`

## Offline usage

No network, accounts, package registries, or frameworks required:

```bash
make -C impl-c          # y `make -C impl-c smoke`
python3 -c 'import sys; sys.path.insert(0, "src"); import gerarion'
```

## Verification

With Python ≥ 3.9 and `reuse` installed:

```bash
reuse lint                                    # licensing 100 %
make -C impl-c smoke                          # núcleo standalone
```

From `verared/gerarion`, full integrity and (optionally) detached-signature authenticity are verified with:

```bash
python3 tools/export_module.py --verify-existing /path/to/gt-core
# With cryptographic verification of EXPORT-MANIFEST.json.sig:
python3 tools/export_module.py --verify-existing /path/to/gt-core --trusted-pub-key /path/to/release-pub.pem
```

## Synchronisation contract with `verared/gerarion`

This package is **generated, never hand-edited**: it is regenerated
byte for byte from `verared/gerarion v3.3.0` with
`python3 tools/export_module.py --module gt-core --out <dir>`. The
normative source of truth (specifications, CC0 vectors, reference
cores for the three platforms, and the full test suite) stays in
`verared/gerarion`; `verared/gt-core` satellites consume it and never fork the
arithmetic. Updates flow by regenerating the export from a tag of the
base repository — never by editing exported files.
