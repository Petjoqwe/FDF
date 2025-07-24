# 🧪 Test Suite Completo - FDF

## 📋 Descripción

Esta carpeta contiene un conjunto completo de pruebas automatizadas para el proyecto FDF. Los tests cubren todas las funcionalidades críticas del programa, incluyendo parsing, memoria, renderizado isométrico y controles.

## 🗂️ Estructura de Archivos

```
testers/
├── README.md              # Este archivo
├── run_all_tests.sh       # Test suite principal (ejecuta todos los tests)
├── test_parsing.sh        # Tests específicos de parsing
├── test_memory.sh         # Tests de fugas de memoria con Valgrind
├── test_isometric.sh      # Tests de renderizado isométrico
└── test_gnl.c            # Tests de get_next_line
```

## 🚀 Uso Rápido

### Ejecutar Todas las Pruebas
```bash
cd testers/
chmod +x *.sh
./run_all_tests.sh
```

### Ejecutar Tests Específicos
```bash
# Solo pruebas de parsing
./test_parsing.sh

# Solo pruebas de memoria
./test_memory.sh

# Solo pruebas de renderizado
./test_isometric.sh
```

## 📊 Tests Disponibles

### 1. **run_all_tests.sh** - Test Suite Principal
**Propósito**: Ejecuta todas las pruebas en secuencia
**Cubre**:
- ✅ Compilación del proyecto
- ✅ Verificación de Norminette
- ✅ Pruebas de parsing
- ✅ Pruebas de fugas de memoria
- ✅ Pruebas de get_next_line
- ✅ Pruebas de renderizado isométrico
- ✅ Pruebas de controles

**Uso**:
```bash
./run_all_tests.sh
```

### 2. **test_parsing.sh** - Tests de Parsing
**Propósito**: Verifica el parsing correcto de archivos .fdf
**Pruebas incluidas**:
- ✅ Mapas válidos de diferentes tamaños
- ✅ Mapas inválidos (formato incorrecto)
- ✅ Casos edge (valores extremos, espacios extra)
- ✅ Archivos inexistentes
- ✅ Problemas de permisos
- ✅ Extensiones incorrectas

**Uso**:
```bash
./test_parsing.sh
```

### 3. **test_memory.sh** - Tests de Memoria
**Propósito**: Detecta fugas de memoria usando Valgrind
**Pruebas incluidas**:
- ✅ Mapas pequeños, medianos y grandes
- ✅ Valores extremos (muy grandes/pequeños)
- ✅ Casos edge (una línea, una columna)
- ✅ Múltiples ejecuciones para detectar fugas acumulativas
- ✅ Manejo de errores sin fugas

**Requisitos**:
- Valgrind instalado (se instala automáticamente si no está)

**Uso**:
```bash
./test_memory.sh
```

### 4. **test_isometric.sh** - Tests de Renderizado
**Propósito**: Verifica el renderizado isométrico y controles
**Pruebas incluidas**:
- ✅ Renderizado básico con diferentes mapas
- ✅ Casos edge (valores negativos, extremos)
- ✅ Diferentes tamaños de mapa
- ✅ Patrones específicos (ajedrez, gradiente, ondas)
- ✅ Controles básicos
- ✅ Rendimiento y estabilidad

**Uso**:
```bash
./test_isometric.sh
```

### 5. **test_gnl.c** - Tests de Get Next Line
**Propósito**: Verifica la funcionalidad de get_next_line
**Pruebas incluidas**:
- ✅ Lectura básica de archivos
- ✅ Archivos vacíos
- ✅ Una sola línea
- ✅ Líneas vacías
- ✅ Múltiples descriptores de archivo
- ✅ Descriptores inválidos
- ✅ Archivos grandes

**Uso**:
```bash
# Se ejecuta automáticamente desde run_all_tests.sh
# O manualmente:
cd ..
gcc -Wall -Wextra -Werror -I./includes -I./libft \
    -o test_gnl testers/test_gnl.c -L./libft -lft
./test_gnl testers/test_gnl.txt
```

## 🎯 Criterios de Éxito

### ✅ Compilación
- El proyecto debe compilar sin warnings
- No debe haber errores de compilación

### ✅ Norminette
- Código debe pasar todas las verificaciones de Norminette
- Sin errores de estilo

### ✅ Parsing
- Debe leer correctamente archivos .fdf válidos
- Debe fallar apropiadamente con archivos inválidos
- Debe manejar casos edge correctamente

### ✅ Memoria
- **CERO** fugas de memoria detectadas por Valgrind
- Liberación correcta en todos los casos
- Sin fugas acumulativas en múltiples ejecuciones

### ✅ Renderizado
- Renderizado isométrico correcto
- Controles responsivos
- Manejo de diferentes tamaños de mapa
- Rendimiento aceptable

### ✅ Get Next Line
- Lectura correcta de archivos
- Manejo apropiado de casos edge
- Sin fugas de memoria

## 📈 Reportes

Cada script genera un reporte detallado que incluye:

- **Estadísticas**: Total de pruebas, exitosas, fallidas
- **Tasa de éxito**: Porcentaje de pruebas que pasaron
- **Detalles de errores**: Información específica sobre fallos
- **Consejos**: Sugerencias para corregir problemas

### Ejemplo de Reporte
```
========================================
Reporte Final de Pruebas
========================================
📊 Estadísticas:
   Total de pruebas: 25
   ✅ Exitosas: 23
   ❌ Fallidas: 2

📈 Tasa de éxito: 92%
```

## 🔧 Configuración

### Requisitos del Sistema
- **Linux** (probado en Ubuntu/Debian)
- **Bash** (para scripts de prueba)
- **Valgrind** (se instala automáticamente)
- **bc** (para cálculos de tiempo)
- **timeout** (comando del sistema)

### Instalación de Dependencias
```bash
# Instalar Valgrind si no está disponible
sudo apt-get update
sudo apt-get install valgrind

# Dar permisos de ejecución a los scripts
chmod +x *.sh
```

## 🚨 Solución de Problemas

### Error: "fdf no encontrado"
```bash
# Asegúrate de compilar el proyecto primero
cd ..
make
cd testers/
./run_all_tests.sh
```

### Error: "Valgrind no encontrado"
```bash
# El script intentará instalarlo automáticamente
# Si falla, instálalo manualmente:
sudo apt-get install valgrind
```

### Timeouts en las Pruebas
- Los timeouts están configurados para evitar bloqueos
- Si tu programa es lento, considera optimizarlo
- Puedes aumentar los timeouts editando los scripts

### Fugas de Memoria Detectadas
1. Revisa los logs de Valgrind para detalles
2. Verifica que todas las llamadas a `malloc()` tengan su `free()`
3. Asegúrate de liberar memoria en casos de error
4. Revisa las funciones de limpieza en `main()`

## 📝 Personalización

### Añadir Nuevas Pruebas
1. Crea un nuevo script de prueba
2. Sigue el formato de los scripts existentes
3. Añade la llamada al script en `run_all_tests.sh`

### Modificar Timeouts
Edita los valores de `timeout` en los scripts:
```bash
# Cambiar de 10s a 30s
timeout 30s "$EXECUTABLE" "$map" > /dev/null 2>&1
```

### Añadir Nuevos Mapas de Prueba
Edita las funciones `create_*_test_maps()` en los scripts correspondientes.

## 🎉 Resultados Esperados

Un proyecto FDF exitoso debería mostrar:

```
🎉 ¡Todas las pruebas pasaron!
✅ El proyecto FDF está listo para evaluación
📈 Tasa de éxito: 100%
```

## 📞 Soporte

Si encuentras problemas con los tests:

1. **Verifica los requisitos**: Asegúrate de que todas las dependencias estén instaladas
2. **Revisa los logs**: Los scripts generan logs detallados para debugging
3. **Ejecuta tests individuales**: Usa los scripts específicos para aislar problemas
4. **Consulta la documentación**: Revisa los READMEs del proyecto principal

---

**💡 Consejo**: Ejecuta los tests regularmente durante el desarrollo para detectar problemas temprano. 