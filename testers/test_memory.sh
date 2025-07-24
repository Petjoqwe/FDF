#!/bin/bash

# =============================================================================
# Test de Fugas de Memoria - FDF
# =============================================================================
# Pruebas específicas para detectar fugas de memoria usando Valgrind

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
PURPLE='\033[0;35m'
NC='\033[0m'

# Variables
PROJECT_DIR=".."
EXECUTABLE="$PROJECT_DIR/fdf"
TOTAL_TESTS=0
PASSED_TESTS=0

# Función para imprimir resultados
print_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✅ $2${NC}"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}❌ $2${NC}"
    fi
    ((TOTAL_TESTS++))
}

# Función para verificar si valgrind está disponible
check_valgrind() {
    if ! command -v valgrind &> /dev/null; then
        echo -e "${YELLOW}⚠️  Valgrind no encontrado. Instalando...${NC}"
        sudo apt-get update > /dev/null 2>&1
        sudo apt-get install -y valgrind > /dev/null 2>&1
        
        if ! command -v valgrind &> /dev/null; then
            echo -e "${RED}❌ Error: No se pudo instalar Valgrind${NC}"
            echo -e "${YELLOW}💡 Instala Valgrind manualmente: sudo apt-get install valgrind${NC}"
            exit 1
        fi
    fi
    echo -e "${GREEN}✅ Valgrind disponible${NC}"
}

# Función para crear mapas de prueba para memoria
create_memory_test_maps() {
    echo -e "${CYAN}📝 Creando mapas de prueba para memoria...${NC}"
    
    # Mapa pequeño
    cat > memory_test_small.fdf << EOF
0 1 2
1 2 3
2 3 4
EOF

    # Mapa mediano
    cat > memory_test_medium.fdf << EOF
0 1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9 10
2 3 4 5 6 7 8 9 10 11
3 4 5 6 7 8 9 10 11 12
4 5 6 7 8 9 10 11 12 13
5 6 7 8 9 10 11 12 13 14
6 7 8 9 10 11 12 13 14 15
7 8 9 10 11 12 13 14 15 16
8 9 10 11 12 13 14 15 16 17
9 10 11 12 13 14 15 16 17 18
EOF

    # Mapa grande
    cat > memory_test_large.fdf << EOF
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0
0 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 1 0
0 1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2 1 0
0 1 2 3 4 4 4 4 4 4 4 4 4 4 4 4 3 2 1 0
0 1 2 3 4 5 5 5 5 5 5 5 5 5 5 4 3 2 1 0
0 1 2 3 4 5 6 6 6 6 6 6 6 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 7 7 7 7 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 8 8 8 8 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 8 9 9 8 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 8 9 9 8 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 8 8 8 8 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 7 7 7 7 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 6 6 6 6 6 6 6 5 4 3 2 1 0
0 1 2 3 4 5 5 5 5 5 5 5 5 5 5 4 3 2 1 0
0 1 2 3 4 4 4 4 4 4 4 4 4 4 4 4 3 2 1 0
0 1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2 1 0
0 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 1 0
0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
EOF

    # Mapa con valores extremos
    cat > memory_test_extreme.fdf << EOF
-999999 999999 -999999
999999 -999999 999999
-999999 999999 -999999
EOF

    # Mapa rectangular
    cat > memory_test_rectangular.fdf << EOF
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
EOF

    echo -e "${GREEN}✅ Mapas de prueba para memoria creados${NC}"
}

# Función para ejecutar valgrind en un mapa
run_valgrind_test() {
    local map_file="$1"
    local test_name="$2"
    
    echo -e "${CYAN}🔍 Probando $test_name con Valgrind...${NC}"
    
    # Ejecutar valgrind con timeout
    timeout 30s valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --verbose \
        --log-file="valgrind_${test_name}.log" \
        "$EXECUTABLE" "$map_file" > /dev/null 2>&1
    
    local valgrind_exit=$?
    
    # Verificar si valgrind se ejecutó correctamente
    if [ $valgrind_exit -eq 124 ]; then
        echo -e "${YELLOW}⚠️  Timeout en Valgrind para $test_name${NC}"
        return 1
    fi
    
    # Analizar el log de valgrind
    if [ -f "valgrind_${test_name}.log" ]; then
        # Verificar fugas de memoria
        local definitely_lost=$(grep "definitely lost:" "valgrind_${test_name}.log" | grep -o "[0-9]* bytes")
        local indirectly_lost=$(grep "indirectly lost:" "valgrind_${test_name}.log" | grep -o "[0-9]* bytes")
        local possibly_lost=$(grep "possibly lost:" "valgrind_${test_name}.log" | grep -o "[0-9]* bytes")
        
        # Extraer solo los números
        definitely_lost=$(echo "$definitely_lost" | grep -o "[0-9]*" | head -1)
        indirectly_lost=$(echo "$indirectly_lost" | grep -o "[0-9]*" | head -1)
        possibly_lost=$(echo "$possibly_lost" | grep -o "[0-9]*" | head -1)
        
        # Si no se encontró, asumir 0
        definitely_lost=${definitely_lost:-0}
        indirectly_lost=${indirectly_lost:-0}
        possibly_lost=${possibly_lost:-0}
        
        # Verificar si hay fugas
        if [ "$definitely_lost" -eq 0 ] && [ "$indirectly_lost" -eq 0 ]; then
            print_result 0 "Valgrind - $test_name (sin fugas)"
            return 0
        else
            print_result 1 "Valgrind - $test_name (fugas detectadas)"
            echo -e "${YELLOW}📋 Revisa valgrind_${test_name}.log para detalles${NC}"
            echo -e "${RED}   Definitely lost: ${definitely_lost} bytes${NC}"
            echo -e "${RED}   Indirectly lost: ${indirectly_lost} bytes${NC}"
            echo -e "${YELLOW}   Possibly lost: ${possibly_lost} bytes${NC}"
            return 1
        fi
    else
        print_result 1 "Valgrind - $test_name (no se generó log)"
        return 1
    fi
}

# Función para probar fugas de memoria con diferentes mapas
test_memory_leaks() {
    echo -e "\n${BLUE}🔍 Probando fugas de memoria...${NC}"
    
    # Probar con mapas de diferentes tamaños
    run_valgrind_test "memory_test_small.fdf" "mapa_pequeño"
    run_valgrind_test "memory_test_medium.fdf" "mapa_mediano"
    run_valgrind_test "memory_test_large.fdf" "mapa_grande"
    run_valgrind_test "memory_test_extreme.fdf" "valores_extremos"
    run_valgrind_test "memory_test_rectangular.fdf" "mapa_rectangular"
}

# Función para probar casos edge de memoria
test_memory_edge_cases() {
    echo -e "\n${BLUE}🔍 Probando casos edge de memoria...${NC}"
    
    # Mapa con una sola línea
    cat > memory_test_single_line.fdf << EOF
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
EOF
    run_valgrind_test "memory_test_single_line.fdf" "una_sola_línea"
    
    # Mapa con una sola columna
    cat > memory_test_single_column.fdf << EOF
0
1
2
3
4
5
6
7
8
9
EOF
    run_valgrind_test "memory_test_single_column.fdf" "una_sola_columna"
    
    # Mapa con valores muy grandes
    cat > memory_test_very_large_values.fdf << EOF
2147483647 2147483647 2147483647
2147483647 2147483647 2147483647
2147483647 2147483647 2147483647
EOF
    run_valgrind_test "memory_test_very_large_values.fdf" "valores_muy_grandes"
    
    # Mapa con valores muy pequeños
    cat > memory_test_very_small_values.fdf << EOF
-2147483648 -2147483648 -2147483648
-2147483648 -2147483648 -2147483648
-2147483648 -2147483648 -2147483648
EOF
    run_valgrind_test "memory_test_very_small_values.fdf" "valores_muy_pequeños"
}

# Función para probar errores de memoria
test_memory_errors() {
    echo -e "\n${BLUE}🔍 Probando errores de memoria...${NC}"
    
    # Probar con archivo inexistente
    timeout 10s valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --verbose \
        --log-file="valgrind_error_nonexistent.log" \
        "$EXECUTABLE" "archivo_que_no_existe.fdf" > /dev/null 2>&1
    
    if [ -f "valgrind_error_nonexistent.log" ]; then
        local definitely_lost=$(grep "definitely lost:" "valgrind_error_nonexistent.log" | grep -o "[0-9]* bytes" | grep -o "[0-9]*" | head -1)
        definitely_lost=${definitely_lost:-0}
        
        if [ "$definitely_lost" -eq 0 ]; then
            print_result 0 "Error - archivo inexistente (sin fugas)"
        else
            print_result 1 "Error - archivo inexistente (fugas detectadas)"
        fi
    else
        print_result 1 "Error - archivo inexistente (no se generó log)"
    fi
    
    # Probar con archivo vacío
    touch memory_test_empty.fdf
    run_valgrind_test "memory_test_empty.fdf" "archivo_vacío"
}

# Función para probar múltiples ejecuciones
test_multiple_runs() {
    echo -e "\n${BLUE}🔍 Probando múltiples ejecuciones...${NC}"
    
    # Ejecutar el programa múltiples veces para detectar fugas acumulativas
    for i in {1..5}; do
        echo -e "${CYAN}   Ejecución $i/5...${NC}"
        
        timeout 10s valgrind \
            --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --verbose \
            --log-file="valgrind_multiple_${i}.log" \
            "$EXECUTABLE" "memory_test_small.fdf" > /dev/null 2>&1
        
        if [ $? -eq 124 ]; then
            echo -e "${YELLOW}   ⚠️  Timeout en ejecución $i${NC}"
        fi
    done
    
    # Verificar si hay fugas en alguna ejecución
    local has_leaks=0
    for i in {1..5}; do
        if [ -f "valgrind_multiple_${i}.log" ]; then
            local definitely_lost=$(grep "definitely lost:" "valgrind_multiple_${i}.log" | grep -o "[0-9]* bytes" | grep -o "[0-9]*" | head -1)
            definitely_lost=${definitely_lost:-0}
            
            if [ "$definitely_lost" -gt 0 ]; then
                has_leaks=1
                echo -e "${RED}   ❌ Fugas detectadas en ejecución $i${NC}"
            fi
        fi
    done
    
    if [ $has_leaks -eq 0 ]; then
        print_result 0 "Múltiples ejecuciones (sin fugas acumulativas)"
    else
        print_result 1 "Múltiples ejecuciones (fugas acumulativas detectadas)"
    fi
}

# Función para limpiar archivos temporales
cleanup() {
    rm -f memory_test_*.fdf
    rm -f valgrind_*.log
}

# Función para generar reporte
generate_report() {
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}Reporte de Pruebas de Memoria${NC}"
    echo -e "${BLUE}========================================${NC}"
    
    echo -e "${CYAN}📊 Estadísticas:${NC}"
    echo -e "   Total de pruebas: $TOTAL_TESTS"
    echo -e "   ${GREEN}✅ Exitosas: $PASSED_TESTS${NC}"
    echo -e "   ${RED}❌ Fallidas: $((TOTAL_TESTS - PASSED_TESTS))${NC}"
    
    if [ $PASSED_TESTS -eq $TOTAL_TESTS ]; then
        echo -e "\n${GREEN}🎉 ¡Todas las pruebas de memoria pasaron!${NC}"
        echo -e "${GREEN}✅ No se detectaron fugas de memoria${NC}"
    else
        echo -e "\n${RED}⚠️  Se detectaron fugas de memoria${NC}"
        echo -e "${YELLOW}💡 Revisa los logs de Valgrind para más detalles${NC}"
    fi
    
    # Calcular porcentaje de éxito
    if [ $TOTAL_TESTS -gt 0 ]; then
        SUCCESS_RATE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
        echo -e "\n${BLUE}📈 Tasa de éxito: $SUCCESS_RATE%${NC}"
    fi
    
    # Mostrar consejos si hay fugas
    if [ $PASSED_TESTS -lt $TOTAL_TESTS ]; then
        echo -e "\n${YELLOW}💡 Consejos para corregir fugas de memoria:${NC}"
        echo -e "   • Verifica que todas las llamadas a malloc() tengan su free()"
        echo -e "   • Asegúrate de liberar memoria en casos de error"
        echo -e "   • Revisa las funciones de limpieza en main()"
        echo -e "   • Verifica la liberación de estructuras anidadas"
    fi
}

# Función principal
main() {
    echo -e "${PURPLE}🧪 Iniciando pruebas de memoria para FDF...${NC}"
    
    # Verificar que el ejecutable existe
    if [ ! -f "$EXECUTABLE" ]; then
        echo -e "${RED}❌ Error: $EXECUTABLE no encontrado${NC}"
        echo -e "${YELLOW}💡 Ejecuta 'make' en el directorio principal primero${NC}"
        exit 1
    fi
    
    # Verificar valgrind
    check_valgrind
    
    # Crear mapas de prueba
    create_memory_test_maps
    
    # Ejecutar todas las pruebas
    test_memory_leaks
    test_memory_edge_cases
    test_memory_errors
    test_multiple_runs
    
    # Generar reporte
    generate_report
    
    # Limpiar archivos temporales
    cleanup
    
    echo -e "\n${PURPLE}🏁 Pruebas de memoria completadas${NC}"
}

# Ejecutar función principal
main "$@" 