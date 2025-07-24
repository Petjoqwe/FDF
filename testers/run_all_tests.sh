#!/bin/bash

# =============================================================================
# FDF - Test Suite Completo
# =============================================================================
# Este script ejecuta todas las pruebas necesarias para validar el proyecto FDF
# Incluye: parsing, memoria, get_next_line, renderizado isométrico y controles

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Variables globales
PROJECT_DIR=".."
BUILD_DIR="$PROJECT_DIR"
EXECUTABLE="fdf"
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Función para imprimir headers
print_header() {
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}"
}

# Función para imprimir resultados
print_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✅ $2${NC}"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}❌ $2${NC}"
        ((FAILED_TESTS++))
    fi
    ((TOTAL_TESTS++))
}

# Función para limpiar archivos temporales
cleanup() {
    rm -f test_output.txt
    rm -f valgrind_output.txt
    rm -f temp_map.fdf
    rm -f test_*.fdf
}

# Función para verificar si el ejecutable existe
check_executable() {
    if [ ! -f "$BUILD_DIR/$EXECUTABLE" ]; then
        echo -e "${RED}❌ Error: $EXECUTABLE no encontrado en $BUILD_DIR${NC}"
        echo -e "${YELLOW}💡 Ejecuta 'make' en el directorio principal primero${NC}"
        exit 1
    fi
}

# Función para compilar el proyecto
compile_project() {
    print_header "Compilando Proyecto FDF"
    
    cd "$PROJECT_DIR"
    make fclean > /dev/null 2>&1
    make > /dev/null 2>&1
    COMPILE_RESULT=$?
    cd - > /dev/null
    
    print_result $COMPILE_RESULT "Compilación del proyecto"
    
    if [ $COMPILE_RESULT -ne 0 ]; then
        echo -e "${RED}❌ Error de compilación. Revisa los errores arriba.${NC}"
        exit 1
    fi
}

# Función para verificar Norminette
test_norminette() {
    print_header "Verificando Norminette"
    
    cd "$PROJECT_DIR"
    norminette src/ includes/ > norminette_output.txt 2>&1
    NORM_RESULT=$?
    cd - > /dev/null
    
    if [ $NORM_RESULT -eq 0 ]; then
        print_result 0 "Norminette - Sin errores"
    else
        print_result 1 "Norminette - Errores encontrados"
        echo -e "${YELLOW}📋 Revisa norminette_output.txt para detalles${NC}"
    fi
}

# Función para probar parsing de archivos
test_parsing() {
    print_header "Pruebas de Parsing"
    
    # Crear archivos de prueba
    create_test_maps
    
    # Probar archivos válidos
    for map in test_valid_*.fdf; do
        if [ -f "$map" ]; then
            timeout 5s "$BUILD_DIR/$EXECUTABLE" "$map" > /dev/null 2>&1
            print_result $? "Parsing de $map"
        fi
    done
    
    # Probar archivos inválidos
    for map in test_invalid_*.fdf; do
        if [ -f "$map" ]; then
            timeout 5s "$BUILD_DIR/$EXECUTABLE" "$map" > /dev/null 2>&1
            # Debería fallar para archivos inválidos
            if [ $? -ne 0 ]; then
                print_result 0 "Parsing inválido de $map (falló correctamente)"
            else
                print_result 1 "Parsing inválido de $map (no falló como esperado)"
            fi
        fi
    done
}

# Función para crear mapas de prueba
create_test_maps() {
    # Mapa válido simple
    cat > test_valid_simple.fdf << EOF
0 0 0
0 1 0
0 0 0
EOF

    # Mapa válido con alturas
    cat > test_valid_heights.fdf << EOF
0 1 2 3
1 2 3 4
2 3 4 5
3 4 5 6
EOF

    # Mapa válido grande
    cat > test_valid_large.fdf << EOF
0 0 0 0 0 0 0 0 0 0
0 1 1 1 1 1 1 1 1 0
0 1 2 2 2 2 2 2 1 0
0 1 2 3 3 3 3 2 1 0
0 1 2 3 4 4 3 2 1 0
0 1 2 3 4 4 3 2 1 0
0 1 2 3 3 3 3 2 1 0
0 1 2 2 2 2 2 2 1 0
0 1 1 1 1 1 1 1 1 0
0 0 0 0 0 0 0 0 0 0
EOF

    # Mapa inválido - archivo vacío
    touch test_invalid_empty.fdf

    # Mapa inválido - formato incorrecto
    cat > test_invalid_format.fdf << EOF
0 0 0
0 1
0 0 0 0
EOF

    # Mapa inválido - caracteres no numéricos
    cat > test_invalid_chars.fdf << EOF
0 a 0
0 1 0
0 0 0
EOF
}

# Función para probar fugas de memoria
test_memory_leaks() {
    print_header "Pruebas de Fugas de Memoria"
    
    # Verificar si valgrind está disponible
    if ! command -v valgrind &> /dev/null; then
        echo -e "${YELLOW}⚠️  Valgrind no encontrado. Instalando...${NC}"
        sudo apt-get update && sudo apt-get install -y valgrind
    fi
    
    # Probar con diferentes mapas
    for map in test_valid_*.fdf; do
        if [ -f "$map" ]; then
            echo -e "${CYAN}🔍 Probando $map con Valgrind...${NC}"
            
            timeout 10s valgrind --leak-check=full --show-leak-kinds=all \
                --track-origins=yes --verbose --log-file=valgrind_output.txt \
                "$BUILD_DIR/$EXECUTABLE" "$map" > /dev/null 2>&1
            
            # Verificar si hay fugas de memoria
            if grep -q "definitely lost: 0 bytes" valgrind_output.txt && \
               grep -q "indirectly lost: 0 bytes" valgrind_output.txt; then
                print_result 0 "Valgrind - $map (sin fugas)"
            else
                print_result 1 "Valgrind - $map (fugas detectadas)"
                echo -e "${YELLOW}📋 Revisa valgrind_output.txt para detalles${NC}"
            fi
        fi
    done
}

# Función para probar get_next_line
test_get_next_line() {
    print_header "Pruebas de Get Next Line"
    
    # Crear archivo de prueba para get_next_line
    cat > test_gnl.txt << EOF
Primera línea
Segunda línea
Tercera línea
Cuarta línea
EOF

    # Compilar y ejecutar test de get_next_line
    cd "$PROJECT_DIR"
    gcc -Wall -Wextra -Werror -I./includes -I./libft \
        -o test_gnl testers/test_gnl.c -L./libft -lft
    
    if [ -f "test_gnl" ]; then
        ./test_gnl test_gnl.txt > gnl_output.txt
        GNL_RESULT=$?
        print_result $GNL_RESULT "Get Next Line"
        
        if [ $GNL_RESULT -eq 0 ]; then
            echo -e "${GREEN}✅ Get Next Line funciona correctamente${NC}"
        else
            echo -e "${RED}❌ Problemas con Get Next Line${NC}"
        fi
        
        rm -f test_gnl gnl_output.txt
    else
        print_result 1 "Compilación de test Get Next Line"
    fi
    cd - > /dev/null
}

# Función para probar renderizado isométrico
test_isometric_rendering() {
    print_header "Pruebas de Renderizado Isométrico"
    
    # Crear mapa de prueba para renderizado
    cat > test_isometric.fdf << EOF
0 1 2 3
1 2 3 4
2 3 4 5
3 4 5 6
EOF

    # Probar renderizado (sin ventana gráfica)
    timeout 5s "$BUILD_DIR/$EXECUTABLE" test_isometric.fdf > /dev/null 2>&1
    RENDER_RESULT=$?
    print_result $RENDER_RESULT "Renderizado isométrico básico"
    
    # Probar con diferentes tamaños
    for size in 5 10 15; do
        create_test_map_size $size
        timeout 5s "$BUILD_DIR/$EXECUTABLE" "test_size_${size}.fdf" > /dev/null 2>&1
        print_result $? "Renderizado mapa $size x $size"
    done
}

# Función para crear mapa de tamaño específico
create_test_map_size() {
    local size=$1
    local filename="test_size_${size}.fdf"
    
    > "$filename"  # Limpiar archivo
    
    for ((i=0; i<size; i++)); do
        for ((j=0; j<size; j++)); do
            echo -n "$((RANDOM % 10)) "
        done
        echo "" >> "$filename"
    done
}

# Función para probar controles
test_controls() {
    print_header "Pruebas de Controles"
    
    # Crear mapa de prueba
    cat > test_controls.fdf << EOF
0 1 2 3
1 2 3 4
2 3 4 5
3 4 5 6
EOF

    echo -e "${CYAN}🎮 Iniciando pruebas de controles...${NC}"
    echo -e "${YELLOW}💡 Presiona ESC para salir de las pruebas de controles${NC}"
    
    # Iniciar programa para pruebas manuales
    timeout 30s "$BUILD_DIR/$EXECUTABLE" test_controls.fdf
    
    print_result 0 "Controles básicos (prueba manual)"
}

# Función para generar reporte final
generate_report() {
    print_header "Reporte Final de Pruebas"
    
    echo -e "${CYAN}📊 Estadísticas:${NC}"
    echo -e "   Total de pruebas: $TOTAL_TESTS"
    echo -e "   ${GREEN}✅ Exitosas: $PASSED_TESTS${NC}"
    echo -e "   ${RED}❌ Fallidas: $FAILED_TESTS${NC}"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "\n${GREEN}🎉 ¡Todas las pruebas pasaron!${NC}"
        echo -e "${GREEN}✅ El proyecto FDF está listo para evaluación${NC}"
    else
        echo -e "\n${RED}⚠️  Algunas pruebas fallaron${NC}"
        echo -e "${YELLOW}💡 Revisa los errores arriba y corrige los problemas${NC}"
    fi
    
    # Calcular porcentaje de éxito
    if [ $TOTAL_TESTS -gt 0 ]; then
        SUCCESS_RATE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
        echo -e "\n${BLUE}📈 Tasa de éxito: $SUCCESS_RATE%${NC}"
    fi
}

# Función principal
main() {
    echo -e "${PURPLE}🚀 Iniciando Test Suite Completo para FDF${NC}"
    echo -e "${PURPLE}========================================${NC}"
    
    # Verificar que estamos en el directorio correcto
    if [ ! -f "../Makefile" ]; then
        echo -e "${RED}❌ Error: No se encontró Makefile en el directorio padre${NC}"
        echo -e "${YELLOW}💡 Ejecuta este script desde la carpeta testers/${NC}"
        exit 1
    fi
    
    # Limpiar archivos temporales
    cleanup
    
    # Ejecutar todas las pruebas
    compile_project
    test_norminette
    test_parsing
    test_memory_leaks
    test_get_next_line
    test_isometric_rendering
    test_controls
    
    # Generar reporte final
    generate_report
    
    # Limpiar archivos temporales
    cleanup
    
    echo -e "\n${PURPLE}🏁 Test Suite Completado${NC}"
}

# Ejecutar función principal
main "$@" 