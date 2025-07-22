# FDF - Wireframe Model Renderer

## 📋 Descripción del Proyecto

FDF (Fil de Fer) es un proyecto de renderizado 3D que representa modelos wireframe de paisajes utilizando proyección isométrica. El programa lee archivos `.fdf` que contienen mapas de altura y los visualiza en una ventana gráfica usando MLX42.

## 🎯 Objetivos Principales

1. Leer y parsear archivos `.fdf` con mapas de altura
2. Renderizar el mapa en proyección isométrica
3. Mostrar el modelo como wireframe (malla de líneas)
4. Gestionar eventos de ventana y teclado
5. Mantener una arquitectura modular y limpia

## 📏 Restricciones Obligatorias

### Norminette
- ✅ Cada archivo `.c` debe tener **máximo 5 funciones**
- ✅ Cada función debe tener **máximo 25 líneas**
- ✅ **NO** usar variables globales
- ✅ **NO** fugas de memoria
- ✅ Todo el código debe pasar la Norminette

### Técnicas
- ✅ Usar **MLX42** (NO MiniLibX)
- ✅ Incluir Makefile funcional con reglas obligatorias
- ✅ Gestión correcta de errores sin crashes
- ✅ Liberación completa de memoria

## 📁 Estructura del Proyecto

```
fdf/
├── Makefile
├── includes/
│   ├── fdf.h          # Header principal con estructuras generales
│   ├── map.h          # Estructuras y funciones de parseo
│   ├── render.h       # Funciones de renderizado
│   ├── events.h       # Gestión de eventos
│   └── utils.h        # Utilidades generales
├── srcs/
│   ├── main.c         # Flujo principal del programa
│   ├── parse_map.c    # Lectura y procesamiento de archivos .fdf
│   ├── render.c       # Renderizado isométrico y dibujo
│   ├── events.c       # Gestión de eventos MLX42
│   └── utils.c        # Funciones auxiliares
├── libft/             # Librería libft completa
│   ├── Makefile
│   └── [archivos libft...]
└── maps/              # Mapas de prueba .fdf (opcional)
```

## 🔧 Responsabilidades de cada Archivo

### 1. `main.c` - Control de Flujo Principal
**Responsabilidades:**
- Validar argumentos de entrada
- Inicializar estructuras principales
- Coordinar el flujo del programa
- Gestionar el ciclo de vida de MLX42
- Asegurar limpieza de recursos

**Funciones (máx. 5):**
```c
int     main(int argc, char **argv);
t_fdf   *init_fdf(char *filename);
void    init_mlx(t_fdf *fdf);
void    run_fdf(t_fdf *fdf);
void    cleanup_fdf(t_fdf *fdf);
```

### 2. `parse_map.c` - Procesamiento de Mapas
**Responsabilidades:**
- Abrir y leer archivos .fdf
- Validar formato del archivo
- Convertir texto a estructura de datos
- Detectar dimensiones del mapa
- Almacenar alturas y colores (si aplica)

**Funciones (máx. 5):**
```c
t_map   *parse_map(char *filename);
int     get_map_dimensions(char *filename, t_map *map);
int     **allocate_map_array(int width, int height);
int     fill_map_data(int fd, t_map *map);
void    validate_map_line(char *line, int expected_width);
```

### 3. `render.c` - Renderizado Gráfico
**Responsabilidades:**
- Aplicar proyección isométrica
- Dibujar líneas entre puntos
- Centrar el modelo en pantalla
- Aplicar transformaciones (escala, rotación)
- Actualizar la imagen en MLX42

**Funciones (máx. 5):**
```c
void    render_map(t_fdf *fdf);
void    draw_wireframe(t_fdf *fdf);
t_point project_iso(int x, int y, int z, t_fdf *fdf);
void    draw_line(t_point p1, t_point p2, t_fdf *fdf);
void    clear_image(mlx_image_t *img);
```

### 4. `events.c` - Gestión de Eventos
**Responsabilidades:**
- Capturar eventos de teclado
- Gestionar cierre de ventana
- Procesar comandos del usuario (ESC, etc.)
- Coordinar con funciones de limpieza

**Funciones (máx. 5):**
```c
void    setup_hooks(t_fdf *fdf);
void    key_hook(mlx_key_data_t keydata, void *param);
void    close_hook(void *param);
void    handle_escape(t_fdf *fdf);
void    handle_window_close(t_fdf *fdf);
```

### 5. `utils.c` - Utilidades Generales
**Responsabilidades:**
- Funciones matemáticas auxiliares
- Gestión de errores común
- Liberación de memoria estructurada
- Conversiones y validaciones
- Funciones helper genéricas

**Funciones (máx. 5):**
```c
void    error_exit(char *message);
void    free_map(t_map *map);
void    free_split(char **split);
int     ft_abs(int n);
int     get_color(int z, int z_min, int z_max);
```

## 📊 Estructuras de Datos Principales

```c
// fdf.h
typedef struct s_point
{
    int x;
    int y;
    int color;
}   t_point;

typedef struct s_map
{
    int     **heights;
    int     **colors;
    int     width;
    int     height;
    int     z_min;
    int     z_max;
}   t_map;

typedef struct s_fdf
{
    mlx_t       *mlx;
    mlx_image_t *img;
    t_map       *map;
    int         win_width;
    int         win_height;
    double      scale;
    double      z_scale;
}   t_fdf;
```

## 🔄 Flujo del Programa

```
main.c: Inicio
    ↓
Validar argumentos
    ↓
parse_map.c: Cargar mapa .fdf
    ↓
main.c: Inicializar MLX42
    ↓
render.c: Renderizar wireframe
    ↓
events.c: Configurar eventos
    ↓
main.c: Loop MLX42
    ↓
¿Evento? ──ESC/Close──> utils.c: Liberar memoria
    │                            ↓
    └──Continuar──┘      main.c: Terminar
```

## 🛠️ Makefile

```makefile
NAME        = fdf
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
MLX42_FLAGS = -lmlx42 -lglfw -L"/opt/homebrew/lib" -lm
INCLUDES    = -I./includes -I./libft -I/opt/homebrew/include

SRCS_DIR    = srcs/
SRCS        = main.c parse_map.c render.c events.c utils.c
OBJS        = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

LIBFT       = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42_FLAGS) -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
```

## 🎮 Uso del Programa

```bash
./fdf maps/test_map.fdf
```

### Controles:
- **ESC**: Cerrar el programa
- **Click en X**: Cerrar ventana

## 📝 Formato de Archivo .fdf

```
0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0
0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0
```

Cada número representa la altura (coordenada Z) en ese punto del mapa.

## ⚠️ Gestión de Errores

El programa debe manejar correctamente:
- Archivos inexistentes
- Formatos de archivo inválidos
- Mapas vacíos o mal formados
- Falta de memoria
- Errores de MLX42

## 🧹 Gestión de Memoria

**Obligatorio:**
- Liberar toda la memoria del mapa
- Destruir imágenes MLX42
- Cerrar ventana MLX42
- Liberar estructuras auxiliares
- Verificar con valgrind/fsanitize

## 📌 Notas Importantes para IA

1. **Modularidad estricta**: Cada archivo tiene su propósito específico
2. **Sin mezclar responsabilidades**: El parseo no dibuja, el render no gestiona eventos
3. **Flujo unidireccional**: main → parse → render → events → cleanup
4. **Error handling robusto**: Nunca crashear, siempre salida limpia
5. **Memoria limpia**: TODO lo que se reserve DEBE liberarse

## 🚀 Extras (Bonus)

Si implementas funcionalidades extra:
- Zoom in/out
- Rotación del modelo
- Traslación con teclas
- Cambio de proyección
- Gradientes de color por altura

Recuerda añadir la regla `bonus` al Makefile.

---

**Este README está diseñado específicamente para guiar a Cursor.sh y Claude Opus 4 en la implementación correcta del proyecto FDF, respetando todas las restricciones y manteniendo una arquitectura limpia y modular.**