# Núcleo autónomo TCJ + GUS

Parte de la suite de referencia **Gerarion** (verared/gerarion `v3.2.0`,
Gerarion Universal Standard). Este directorio es un **paquete de
exportación** listo para publicarse (o consumirse) como repositorio
satélite `verared/gt-core`; conserva las rutas relativas del repositorio
base para componer módulos.

## El problema único que resuelve

El núcleo normativo mínimo: calendario AY/DY con Gran Tempalum, formato canónico de 32/29 caracteres, quick_verify e instantes int64 + nanos. Apto para microcontroladores y despliegues bare-metal: sin malloc, sin reloj de SO, sin tabla TAI−UTC y sin dependencias.

## Estado normativo

- **Estable** — línea base `v3.2.0` (aritmética y vectores
  congelados: GUS v3.0.0).
- Especificación(es) incluida(s): `docs/specs/TCJ.es.md`, `docs/specs/TCJ.en.md`, `docs/specs/GUS.es.md`, `docs/specs/GUS.en.md`

## Dependencias

- **Ninguna externa: 100 % standalone.** Puede adoptarse aisladamente, sin el resto de la suite.

## Contenido

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

## Uso offline

No requiere red, cuentas, registro de paquetes ni frameworks:

```bash
make -C impl-c          # y `make -C impl-c smoke`
python3 -c 'import sys; sys.path.insert(0, "src"); import gerarion'
```

## Verificación

Con Python ≥ 3.9 y `reuse` instalado:

```bash
reuse lint                                    # licencias al 100 %
make -C impl-c smoke                          # núcleo standalone
```

## Contrato de sincronización con `verared/gerarion`

Este paquete es **generado, no editado a mano**: se regenera byte a
byte desde `verared/gerarion v3.2.0` con
`python3 tools/export_module.py --module gt-core --out <dir>`. La fuente
de verdad normativa (especificaciones, vectores CC0, núcleos de
referencia de las tres plataformas y la batería completa) permanece en
`verared/gerarion`; los satélites `verared/gt-core` la consumen y no forkean la
aritmética. Las actualizaciones fluyen regenerando la exportación desde
un tag del repositorio base; nunca editando los archivos exportados.
