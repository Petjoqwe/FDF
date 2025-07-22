# FDF - Wireframe Model

## Descripción

FDF (Fil de Fer) es un proyecto de representación 3D en wireframe usando la librería gráfica MLX42. El programa lee un archivo .fdf con coordenadas y alturas, y muestra una proyección isométrica del modelo en una ventana gráfica.

## Estructura del Proyecto

```
fdf/
├── include/          # Headers del proyecto
│   ├── fdf.h        # Header principal con estructuras
│   ├── map.h        # Declaraciones para parseo de mapas
│   ├── render.h     # Declaraciones para renderizado
│   ├── events.h     # Declaraciones para gestión de eventos
│   └── utils.h      # Declaraciones de utilidades
├── src/             # Código fuente
│   ├── main.c       # Punto de entrada y flujo principal
│   ├── parse_map.c  # Lectura y parseo de archivos .fdf
│   ├── parse_map_utils.c # Funciones auxiliares de parseo
│   ├── render.c     # Renderizado del wireframe
│   ├── render_utils.c # Funciones auxiliares de renderizado
│   ├── events.c     # Gestión de eventos de teclado/ventana
│   └── utils.c      # Funciones utilitarias generales
├── libft/           # Librería personal con funciones básicas
├── maps/            # Mapas de ejemplo
└── Makefile         # Sistema de compilación
```

## Normas del Proyecto

- **Máximo 5 funciones por archivo .c**
- **Máximo 25 líneas por función**
- **Sin variables globales**
- **Sin fugas de memoria**
- **Cumplir Norminette**
- **Usar MLX42 (no MiniLibX)**

## Flujo del Programa

1. **main.c**: Valida argumentos → carga mapa → inicializa MLX42 → renderiza → gestiona eventos
2. **parse_map.c**: Lee archivo .fdf → valida formato → crea estructura de datos
3. **render.c**: Proyecta puntos → dibuja líneas horizontales y verticales
4. **events.c**: Maneja teclado (ESC, zoom, translación) → cierre limpio
5. **utils.c**: Gestión de errores y memoria

## Compilación

```bash
make        # Compila el proyecto
make clean  # Elimina archivos objeto
make fclean # Elimina archivos objeto y ejecutables
make re     # Recompila todo desde cero
```

## Uso

```bash
./fdf maps/test_map.fdf
```

## Controles

- **ESC**: Cerrar programa
- **Flechas**: Mover el modelo
- **+/-**: Zoom in/out

## Formato de Archivos .fdf

Los archivos .fdf contienen una matriz de alturas:
```
0 0 0 0
0 1 2 0
0 2 1 0
0 0 0 0
```

Opcionalmente con colores en hexadecimal:
```
0 0 0
0 10,0xFF0000 0
0 0 0
```

## Dependencias

- MLX42
- GLFW
- OpenGL
- Math library

## Instalación de MLX42

```bash
# Clonar MLX42
git clone https://github.com/codam-coding-college/MLX42.git
cd MLX42

# Compilar
cmake -B build
cmake --build build -j4

# Instalar (opcional)
sudo cmake --install build
```

## Notas Importantes

- El proyecto está modularizado estrictamente según las normas
- Cada módulo tiene responsabilidades claras y separadas
- La gestión de memoria es crítica: todo malloc debe tener su free
- El Makefile no debe hacer relink innecesario
