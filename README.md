# Standalone TCJ + GUS core

Part of the **Gerarion** reference suite (verared/gerarion `v3.2.0`,
Gerarion Universal Standard). This directory is an **export package**
ready to be published (or consumed) as the `verared/gt-core` satellite
repository; it keeps the base repository's relative layout so modules
compose cleanly.

## The unique problem it solves

The minimum normative core: AY/DY calendar with Great Tempalum, canonical 32/29-character format, quick_verify, and int64 + nanos instants. Fit for microcontrollers and bare metal: no malloc, no OS clock, no TAI−UTC table, no dependencies.

## Normative status

- **Estable** — baseline `v3.2.0` (frozen arithmetic and vectors:
  GUS v3.0.0).
- Included specification(s): `docs/specs/TCJ.es.md`, `docs/specs/TCJ.en.md`, `docs/specs/GUS.es.md`, `docs/specs/GUS.en.md`

## Dependencies

- **None: 100 % standalone.** May be adopted independently from the rest of the suite.

## Contents

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

## Synchronisation contract with `verared/gerarion`

This package is **generated, never hand-edited**: it is regenerated
byte for byte from `verared/gerarion v3.2.0` with
`python3 tools/export_module.py --module gt-core --out <dir>`. The
normative source of truth (specifications, CC0 vectors, reference
cores for the three platforms, and the full test suite) stays in
`verared/gerarion`; `verared/gt-core` satellites consume it and never fork the
arithmetic. Updates flow by regenerating the export from a tag of the
base repository — never by editing exported files.
