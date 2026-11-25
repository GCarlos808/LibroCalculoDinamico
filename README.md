# Libro de Calculo Dinamico (tipo Excel) - CCC808

Proyecto Final de Programacion 3 (C++ / Qt Widgets + Qt Charts). Grupo de 5.

## Reglas del equipo
- Todo es base 0 internamente ("A1" = fila 0, columna 0). Solo la interfaz muestra "A1".
- PROHIBIDO usar std::vector, std::list, std::queue, std::stack, QList, QMap
  para la matriz, historial, evaluacion, hojas o cola de recalculo.
- Nadie modifica el contenido de una Celda directamente: siempre por
  `LibroTrabajo::establecerContenidoCelda()`.
- Si alguien cambia un header compartido (Tipos.h, Celda.h, HojaCalculo.h,
  LibroTrabajo.h, EvaluadorFormulas.h) avisa al grupo ANTES del merge.
- Una rama por persona (`p1-nucleo`, `p2-motor`, `p3-libro`, `p4-ui`, `p5-archivos`);
  a `main` solo entra codigo que compila.

## Responsables
| # | Rol | Archivos |
|---|-----|----------|
| 1 | Nucleo de datos y memoria | Celda, HojaCalculo, Tipos |
| 2 | Motor de formulas | EvaluadorFormulas, Coordenadas |
| 3 | Libro, historial y recalculo | LibroTrabajo, PilaHistorial, ColaRecalculo |
| 4 | Interfaz grafica y eventos | VentanaPrincipal, TablaHoja |
| 5 | Archivos y herramientas | Serializador, ArchivoCSV, Ordenador, BuscadorReemplazo, GraficoEstadistico |

## Compilar
Qt 6 (con el modulo Qt Charts) + CMake >= 3.16:
```
cmake -S . -B build
cmake --build build
```
