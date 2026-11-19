/*
 * smoke.c — humo del núcleo standalone (export gt-core).
 * Compila y corre SOLO con core/gus_core.h + libgerarion-core.a.
 * Generado por tools/export_module.py de {source} v{version}.
 */

#include "core/gus_core.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    long long di = 0;
    assert(gus_day_index_from_gregorian(2026, 3, 17, &di) == GUS_OK);
    GusDate d;
    assert(gus_to_gerarion(di, &d) == GUS_OK);
    char buf[48];
    GusParsed p;
    p.date = d;
    p.has_time = 0;
    assert(gus_canonical(&p, buf, sizeof(buf)) == GUS_OK);
    printf("gt-core smoke: %s (%lld)\n", buf, di);
    return gus_quick_verify(buf) ? 0 : 1;
}
