# 📋 Documentación de Funciones - FDF

## 🗂️ Estructura de Funciones por Archivo

### 📁 `src/main.c` - Control Principal del Programa

#### `int main(int argc, char **argv)`
- **Propósito**: Punto de entrada principal del programa
- **Parámetros**: 
  - `argc`: Número de argumentos de línea de comandos
  - `argv`: Array de argumentos (argv[1] = nombre del archivo .fdf)
- **Retorna**: 0 en éxito, 1 en error
- **Funcionalidad**:
  - Valida que se proporcione exactamente un argumento
  - Inicializa la estructura principal del programa
  - Ejecuta el bucle principal de renderizado
  - Libera todos los recursos al finalizar

#### `void init_fdf(t_fdf *fdf, char *filename)`
- **Propósito**: Inicializa la estructura principal del programa
- **Parámetros**:
  - `fdf`: Puntero a la estructura principal
  - `filename`: Nombre del archivo .fdf a cargar
- **Funcionalidad**:
  - Parsea el archivo de mapa
  - Inicializa MLX42 y crea la ventana
  - Configura la imagen de renderizado
  - Establece valores iniciales de cámara

#### `void run_fdf(t_fdf *fdf)`
- **Propósito**: Ejecuta el bucle principal de renderizado
- **Parámetros**: `fdf`: Puntero a la estructura principal
- **Funcionalidad**:
  - Configura los hooks de eventos
  - Inicia el bucle principal de MLX42
  - Mantiene la aplicación ejecutándose hasta que se cierre

#### `void cleanup_fdf(t_fdf *fdf)`
- **Propósito**: Libera todos los recursos utilizados
- **Parámetros**: `fdf`: Puntero a la estructura principal
- **Funcionalidad**:
  - Libera la memoria del mapa
  - Cierra la ventana de MLX42
  - Libera la imagen de renderizado
  - Termina la aplicación limpiamente

#### `void handle_error(char *msg, t_fdf *fdf)`
- **Propósito**: Maneja errores de forma centralizada
- **Parámetros**:
  - `msg`: Mensaje de error a mostrar
  - `fdf`: Puntero a la estructura principal (puede ser NULL)
- **Funcionalidad**:
  - Muestra el mensaje de error en stderr
  - Libera recursos si es necesario
  - Termina el programa con código de error

---

### 📁 `src/parse_map.c` - Procesamiento de Archivos de Mapa

#### `t_map *parse_map(char *filename)`
- **Propósito**: Lee y procesa un archivo .fdf completo
- **Parámetros**: `filename`: Ruta al archivo .fdf
- **Retorna**: Puntero a estructura de mapa o NULL en error
- **Funcionalidad**:
  - Abre y valida el archivo
  - Lee las dimensiones del mapa
  - Asigna memoria para los puntos
  - Parsea todos los puntos y alturas

#### `void read_map_dimensions(int fd, t_map *map)`
- **Propósito**: Determina el ancho y alto del mapa
- **Parámetros**:
  - `fd`: Descriptor del archivo abierto
  - `map`: Puntero a la estructura de mapa
- **Funcionalidad**:
  - Cuenta líneas para determinar altura
  - Cuenta elementos en primera línea para ancho
  - Actualiza las dimensiones en la estructura

#### `void parse_map_points(int fd, t_map *map)`
- **Propósito**: Convierte el contenido del archivo en puntos 3D
- **Parámetros**:
  - `fd`: Descriptor del archivo (reposicionado al inicio)
  - `map`: Puntero a la estructura de mapa
- **Funcionalidad**:
  - Lee línea por línea del archivo
  - Convierte cada línea en puntos de coordenadas
  - Actualiza valores mínimos y máximos de altura

#### `void parse_line(char *line, t_map *map, int y)`
- **Propósito**: Procesa una línea individual del archivo .fdf
- **Parámetros**:
  - `line`: Línea de texto a procesar
  - `map`: Puntero a la estructura de mapa
  - `y`: Coordenada Y actual (fila)
- **Funcionalidad**:
  - Divide la línea en valores individuales
  - Convierte cada valor a coordenada 3D
  - Asigna colores basados en altura
  - Almacena puntos en la estructura

#### `void free_map(t_map *map)`
- **Propósito**: Libera la memoria utilizada por el mapa
- **Parámetros**: `map`: Puntero a la estructura de mapa
- **Funcionalidad**:
  - Libera cada fila de puntos
  - Libera el array de filas
  - Establece punteros a NULL

---

### 📁 `src/render.c` - Renderizado Gráfico

#### `void render_map(t_fdf *fdf)`
- **Propósito**: Renderiza el mapa completo en la ventana
- **Parámetros**: `fdf`: Puntero a la estructura principal
- **Funcionalidad**:
  - Limpia la imagen de renderizado
  - Proyecta todos los puntos a coordenadas 2D
  - Dibuja líneas entre puntos adyacentes
  - Actualiza la imagen en la ventana

#### `void project_isometric(t_point *point, t_fdf *fdf)`
- **Propósito**: Convierte coordenadas 3D a proyección isométrica 2D
- **Parámetros**:
  - `point`: Punto 3D a proyectar
  - `fdf`: Puntero a la estructura principal
- **Funcionalidad**:
  - Aplica transformaciones de rotación 3D
  - Convierte a proyección isométrica
  - Aplica zoom y desplazamiento de cámara
  - Actualiza las coordenadas del punto

#### `void draw_line(t_fdf *fdf, t_point start, t_point end)`
- **Propósito**: Dibuja una línea entre dos puntos usando algoritmo de Bresenham
- **Parámetros**:
  - `fdf`: Puntero a la estructura principal
  - `start`: Punto inicial de la línea
  - `end`: Punto final de la línea
- **Funcionalidad**:
  - Calcula diferencias entre puntos
  - Determina dirección de la línea
  - Aplica algoritmo de Bresenham
  - Dibuja píxeles con color interpolado

#### `void clear_image(mlx_image_t *img)`
- **Propósito**: Limpia la imagen de renderizado
- **Parámetros**: `img`: Puntero a la imagen de MLX42
- **Funcionalidad**:
  - Establece todos los píxeles a color negro
  - Prepara la imagen para nuevo renderizado

#### `void put_pixel(mlx_image_t *img, int x, int y, uint32_t color)`
- **Propósito**: Coloca un píxel en la imagen
- **Parámetros**:
  - `img`: Puntero a la imagen de MLX42
  - `x`, `y`: Coordenadas del píxel
  - `color`: Color del píxel en formato RGBA
- **Funcionalidad**:
  - Valida que las coordenadas estén dentro de la imagen
  - Calcula la posición en memoria
  - Escribe el color en la posición correcta

---

### 📁 `src/events.c` - Gestión de Eventos

#### `void setup_hooks(t_fdf *fdf)`
- **Propósito**: Configura todos los hooks de eventos de MLX42
- **Parámetros**: `fdf`: Puntero a la estructura principal
- **Funcionalidad**:
  - Registra función para eventos de teclado
  - Registra función para cierre de ventana
  - Configura parámetros de los hooks

#### `void key_hook(mlx_key_data_t keydata, void *param)`
- **Propósito**: Maneja todos los eventos de teclado
- **Parámetros**:
  - `keydata`: Estructura con información del evento
  - `param`: Puntero a la estructura principal
- **Funcionalidad**:
  - Detecta teclas presionadas
  - Ejecuta acciones correspondientes (movimiento, zoom, rotación)
  - Re-renderiza el mapa después de cambios
  - Maneja salida del programa

#### `void close_hook(void *param)`
- **Propósito**: Maneja el cierre de la ventana
- **Parámetros**: `param`: Puntero a la estructura principal
- **Funcionalidad**:
  - Libera todos los recursos
  - Termina la aplicación limpiamente

#### `void scroll_hook(double xdelta, double ydelta, void *param)`
- **Propósito**: Maneja eventos de scroll del ratón
- **Parámetros**:
  - `xdelta`, `ydelta`: Cambios en scroll horizontal y vertical
  - `param`: Puntero a la estructura principal
- **Funcionalidad**:
  - Ajusta el zoom basado en scroll vertical
  - Re-renderiza el mapa con nuevo zoom

---

### 📁 `src/transform.c` - Transformaciones 3D

#### `void rotate_x(t_point *point, float angle)`
- **Propósito**: Rota un punto alrededor del eje X
- **Parámetros**:
  - `point`: Punto a rotar
  - `angle`: Ángulo de rotación en radianes
- **Funcionalidad**:
  - Aplica matriz de rotación X
  - Actualiza coordenadas Y y Z del punto

#### `void rotate_y(t_point *point, float angle)`
- **Propósito**: Rota un punto alrededor del eje Y
- **Parámetros**:
  - `point`: Punto a rotar
  - `angle`: Ángulo de rotación en radianes
- **Funcionalidad**:
  - Aplica matriz de rotación Y
  - Actualiza coordenadas X y Z del punto

#### `void rotate_z(t_point *point, float angle)`
- **Propósito**: Rota un punto alrededor del eje Z
- **Parámetros**:
  - `point`: Punto a rotar
  - `angle`: Ángulo de rotación en radianes
- **Funcionalidad**:
  - Aplica matriz de rotación Z
  - Actualiza coordenadas X e Y del punto

#### `void apply_rotation(t_point *point, t_fdf *fdf)`
- **Propósito**: Aplica todas las rotaciones acumuladas a un punto
- **Parámetros**:
  - `point`: Punto a transformar
  - `fdf`: Puntero a la estructura principal
- **Funcionalidad**:
  - Aplica rotación X, Y y Z en secuencia
  - Usa los ángulos almacenados en la cámara

#### `void reset_rotation(t_fdf *fdf)`
- **Propósito**: Resetea todas las rotaciones a cero
- **Parámetros**: `fdf`: Puntero a la estructura principal
- **Funcionalidad**:
  - Establece todos los ángulos de rotación a 0
  - Re-renderiza el mapa en posición original

---

### 📁 `src/utils.c` - Funciones Auxiliares

#### `int ft_abs(int n)`
- **Propósito**: Calcula el valor absoluto de un entero
- **Parámetros**: `n`: Número entero
- **Retorna**: Valor absoluto del número
- **Funcionalidad**: Retorna el número sin signo

#### `int ft_max(int a, int b)`
- **Propósito**: Encuentra el máximo entre dos números
- **Parámetros**: `a`, `b`: Números a comparar
- **Retorna**: El número mayor
- **Funcionalidad**: Compara y retorna el valor más alto

#### `void free_split(char **split)`
- **Propósito**: Libera memoria de un array de strings
- **Parámetros**: `split`: Array de strings a liberar
- **Funcionalidad**:
  - Libera cada string individual
  - Libera el array principal
  - Establece puntero a NULL

#### `int get_color(char *str)`
- **Propósito**: Extrae color de una cadena hexadecimal
- **Parámetros**: `str`: String con color en formato "0xRRGGBB"
- **Retorna**: Color en formato entero o color por defecto
- **Funcionalidad**:
  - Parsea color hexadecimal
  - Retorna color por defecto si no hay color válido

#### `void error_exit(char *msg)`
- **Propósito**: Termina el programa con mensaje de error
- **Parámetros**: `msg`: Mensaje de error a mostrar
- **Funcionalidad**:
  - Muestra el mensaje en stderr
  - Termina el programa con código de error 1

---

## 🔄 Flujo de Llamadas de Funciones

### Inicialización
```
main() → init_fdf() → parse_map() → read_map_dimensions() + parse_map_points()
```

### Renderizado
```
render_map() → project_isometric() → apply_rotation() → draw_line() → put_pixel()
```

### Eventos
```
key_hook() → (movimiento/zoom/rotación) → render_map()
```

### Limpieza
```
cleanup_fdf() → free_map() → (MLX42 cleanup)
```

## 📊 Estadísticas de Funciones

- **main.c**: 5 funciones (control principal)
- **parse_map.c**: 5 funciones (procesamiento de archivos)
- **render.c**: 5 funciones (renderizado gráfico)
- **events.c**: 4 funciones (gestión de eventos)
- **transform.c**: 5 funciones (transformaciones 3D)
- **utils.c**: 5 funciones (utilidades)

**Total**: 29 funciones distribuidas en 6 archivos

## ⚠️ Cumplimiento de Normas

✅ **Máximo 5 funciones por archivo**: Todos los archivos cumplen
✅ **Máximo 25 líneas por función**: Todas las funciones cumplen
✅ **Sin variables globales**: No se utilizan variables globales
✅ **Sin fugas de memoria**: Todas las funciones liberan memoria correctamente
✅ **Compatible con Norminette**: Código sigue las normas de estilo 