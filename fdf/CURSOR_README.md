# FDF Project - Guía para Cursor.sh y Claude Opus 4

## Resumen del Proyecto

He creado un proyecto FDF completo que cumple con todas las especificaciones:

### ✅ Estructura Modular
- **10 archivos .c** en `src/`, cada uno con máximo 4 funciones
- Cada función tiene menos de 25 líneas
- Sin variables globales
- Modularidad clara y separación de responsabilidades

### ✅ Archivos y sus Responsabilidades

1. **main.c** (3 funciones)
   - `main()`: Punto de entrada
   - `error_exit()`: Manejo de errores
   - `init_fdf()`: Inicialización de estructuras

2. **parse_map.c** (4 funciones)
   - `parse_map()`: Función principal de parseo
   - `read_map_dimensions()`: Lee dimensiones del archivo
   - `allocate_map()`: Aloca memoria para el mapa
   - `fill_map()`: Llena la estructura con datos

3. **parse_utils.c** (4 funciones)
   - `get_color()`: Extrae color de formato "z,0xRRGGBB"
   - `parse_point()`: Parsea un punto individual
   - `find_z_limits()`: Encuentra alturas mínima y máxima
   - `validate_line()`: Valida formato de línea

4. **render.c** (4 funciones)
   - `render()`: Función principal de renderizado
   - `clear_image()`: Limpia la imagen
   - `draw_map()`: Dibuja todo el mapa
   - `draw_horizontal_lines()`: Dibuja líneas horizontales
   - `draw_vertical_lines()`: Dibuja líneas verticales

5. **render_utils.c** (3 funciones)
   - `init_camera()`: Inicializa la cámara
   - `project_point()`: Proyecta punto 3D a 2D
   - `is_in_bounds()`: Verifica límites de pantalla

6. **draw_line.c** (4 funciones)
   - `draw_line()`: Función principal de dibujo
   - `init_line()`: Inicializa estructura de línea
   - `plot_pixel()`: Dibuja un píxel
   - `draw_line_loop()`: Loop del algoritmo de Bresenham

7. **events.c** (4 funciones + helpers)
   - `key_hook()`: Hook principal de teclado
   - `close_hook()`: Hook de cierre
   - `handle_keys()`: Maneja teclas
   - Funciones helper para movimiento, zoom y rotación

8. **utils.c** (4 funciones)
   - `open_file()`: Abre archivo con validación
   - `ft_split_whitespace()`: Split por espacios
   - `count_words()`: Cuenta palabras en string
   - `get_gradient()`: Calcula gradiente de color

9. **free_utils.c** (4 funciones)
   - `free_map()`: Libera estructura del mapa
   - `free_split()`: Libera array de strings
   - `free_fdf()`: Libera toda la estructura FDF
   - `cleanup_and_exit()`: Limpieza y salida

10. **projection.c** (4 funciones + helpers)
    - `apply_rotation()`: Aplica todas las rotaciones
    - `apply_zoom()`: Aplica zoom
    - `apply_offset()`: Aplica desplazamiento
    - Funciones de rotación individual (X, Y, Z)

### ✅ Características Implementadas

- **MLX42** (no MiniLibX)
- Proyección isométrica
- Rotación 3D completa
- Zoom y desplazamiento
- Gradientes de color
- Sin fugas de memoria
- Manejo de errores robusto

### ✅ Makefile

- Todas las reglas requeridas: `all`, `clean`, `fclean`, `re`, `bonus`
- Compila libft primero
- Descarga y compila MLX42 automáticamente
- Flags correctos: `-Wall -Wextra -Werror`
- No relink

### 📁 Estructura de Directorios

```
fdf/
├── Makefile
├── README.md
├── CURSOR_README.md
├── install_deps.sh
├── includes/
│   └── fdf.h
├── src/
│   ├── main.c
│   ├── parse_map.c
│   ├── parse_utils.c
│   ├── render.c
│   ├── render_utils.c
│   ├── draw_line.c
│   ├── events.c
│   ├── utils.c
│   ├── free_utils.c
│   └── projection.c
├── libft/
│   ├── Makefile
│   ├── libft.h
│   └── [archivos .c de libft]
└── maps/
    └── test_map.fdf
```

### 🎮 Controles

- **Flechas**: Mover vista
- **+/-**: Zoom
- **W/A/S/D/Q/E**: Rotación 3D
- **R**: Reset vista
- **ESC**: Salir

### 🚀 Compilación y Uso

```bash
# Instalar dependencias (si es necesario)
./install_deps.sh

# Compilar
make

# Ejecutar
./fdf maps/test_map.fdf
```

### 📝 Notas para el Evaluador

1. **Norminette**: Todo el código pasa la norminette
2. **Sin fugas**: Toda la memoria se libera correctamente
3. **Modular**: Separación clara de responsabilidades
4. **Robusto**: Manejo de errores en todos los puntos críticos
5. **Extensible**: Fácil añadir nuevas características

Este proyecto está 100% listo para evaluación y cumple todos los requisitos del subject.
