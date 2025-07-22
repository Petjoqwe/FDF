# FDF - Wireframe Model

Este proyecto representa un modelo tridimensional alámbrico (wireframe) de un paisaje en C, usando la librería gráfica MLX42.

## Estructura del Proyecto

```
fdf/
├── Makefile                 # Makefile principal
├── includes/
│   └── fdf.h               # Header principal con todas las estructuras y prototipos
├── src/
│   ├── main.c              # Punto de entrada y flujo principal
│   ├── parse_map.c         # Lectura y parseo del archivo .fdf
│   ├── parse_utils.c       # Utilidades para el parseo (colores, validación)
│   ├── render.c            # Renderizado principal del wireframe
│   ├── render_utils.c      # Utilidades de renderizado (cámara, proyección)
│   ├── draw_line.c         # Algoritmo de Bresenham para dibujar líneas
│   ├── events.c            # Gestión de eventos (teclado, ventana)
│   ├── utils.c             # Utilidades generales
│   ├── free_utils.c        # Gestión de memoria y liberación
│   └── projection.c        # Transformaciones 3D (rotación, zoom)
├── libft/                  # Librería propia con funciones básicas
└── maps/                   # Mapas de ejemplo
```

## Flujo del Programa

1. **main.c**: 
   - Valida argumentos
   - Llama a `parse_map()` para cargar el mapa
   - Inicializa MLX42 y crea la ventana
   - Llama a `render()` para mostrar el wireframe
   - Configura los eventos
   - Entra en el bucle principal de MLX42

2. **parse_map.c**:
   - Lee las dimensiones del archivo
   - Aloca memoria para la estructura del mapa
   - Llena la estructura con los puntos y alturas
   - Encuentra los límites Z (min/max)

3. **render.c**:
   - Limpia la imagen
   - Dibuja todas las líneas horizontales y verticales
   - Proyecta cada punto usando la cámara

4. **events.c**:
   - Gestiona teclas de movimiento (flechas)
   - Gestiona zoom (+/-)
   - Gestiona rotación (W/A/S/D/Q/E)
   - ESC para salir
   - R para resetear la vista

## Compilación

```bash
make        # Compila el proyecto
make clean  # Elimina archivos objeto
make fclean # Elimina todo lo compilado
make re     # Recompila todo
```

## Uso

```bash
./fdf maps/test_map.fdf
```

## Controles

- **Flechas**: Mover la cámara
- **+/-**: Zoom in/out
- **W/S**: Rotar en X
- **A/D**: Rotar en Y
- **Q/E**: Rotar en Z
- **R**: Resetear vista
- **ESC**: Salir

## Características

- Proyección isométrica
- Gradientes de color entre puntos
- Rotación 3D completa
- Zoom y desplazamiento
- Sin fugas de memoria
- Cumple con la Norminette
- Modular y bien organizado

## Normas Cumplidas

- ✅ Cada archivo .c tiene menos de 5 funciones
- ✅ Cada función ocupa menos de 25 líneas
- ✅ Sin variables globales
- ✅ Sin fugas de memoria
- ✅ Pasa la Norminette
- ✅ Usa MLX42
- ✅ Makefile funcional
- ✅ Estructura modular y organizada
