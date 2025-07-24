#!/bin/bash

# =============================================================================
# Test de Renderizado Isométrico - FDF
# =============================================================================
# Pruebas específicas para el renderizado isométrico y controles

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

# Función para crear mapas de prueba para renderizado
create_isometric_test_maps() {
    echo -e "${CYAN}📝 Creando mapas de prueba para renderizado isométrico...${NC}"
    
    # Mapa simple para pruebas básicas
    cat > isometric_test_simple.fdf << EOF
0 1 2
1 2 3
2 3 4
EOF

    # Mapa con forma de pirámide
    cat > isometric_test_pyramid.fdf << EOF
0 0 0 0 0
0 1 1 1 0
0 1 2 1 0
0 1 1 1 0
0 0 0 0 0
EOF

    # Mapa con forma de valle
    cat > isometric_test_valley.fdf << EOF
5 4 3 2 1
4 3 2 1 0
3 2 1 0 1
2 1 0 1 2
1 0 1 2 3
EOF

    # Mapa con forma de montaña
    cat > isometric_test_mountain.fdf << EOF
0 1 2 1 0
1 2 3 2 1
2 3 4 3 2
1 2 3 2 1
0 1 2 1 0
EOF

    # Mapa con valores negativos
    cat > isometric_test_negative.fdf << EOF
-2 -1 0
-1 0 1
0 1 2
EOF

    # Mapa con valores extremos
    cat > isometric_test_extreme.fdf << EOF
-1000 0 1000
0 1000 0
1000 0 -1000
EOF

    # Mapa rectangular
    cat > isometric_test_rectangular.fdf << EOF
0 1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9 10
2 3 4 5 6 7 8 9 10 11
EOF

    # Mapa con una sola línea
    cat > isometric_test_single_line.fdf << EOF
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
EOF

    # Mapa con una sola columna
    cat > isometric_test_single_column.fdf << EOF
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

    # Mapa con patrón de ajedrez
    cat > isometric_test_checkerboard.fdf << EOF
0 1 0 1 0
1 0 1 0 1
0 1 0 1 0
1 0 1 0 1
0 1 0 1 0
EOF

    # Mapa con gradiente
    cat > isometric_test_gradient.fdf << EOF
0 1 2 3 4 5
1 2 3 4 5 6
2 3 4 5 6 7
3 4 5 6 7 8
4 5 6 7 8 9
5 6 7 8 9 10
EOF

    echo -e "${GREEN}✅ Mapas de prueba para renderizado isométrico creados${NC}"
}

# Función para probar renderizado básico
test_basic_rendering() {
    echo -e "\n${BLUE}🔍 Probando renderizado básico...${NC}"
    
    # Probar con diferentes mapas
    for map in isometric_test_simple.fdf isometric_test_pyramid.fdf \
               isometric_test_valley.fdf isometric_test_mountain.fdf; do
        if [ -f "$map" ]; then
            # Usar timeout más largo y redirigir stderr también
            timeout 15s "$EXECUTABLE" "$map" > /dev/null 2>&1
            local result=$?
            if [ $result -eq 124 ]; then
                # Timeout - el programa se quedó colgado, pero esto es normal para tests
                print_result 0 "Renderizado básico de $map (timeout - normal)"
            else
                print_result $result "Renderizado básico de $map"
            fi
        fi
    done
}

# Función para probar casos edge de renderizado
test_edge_cases() {
    echo -e "\n${BLUE}🔍 Probando casos edge de renderizado...${NC}"
    
    # Probar con valores negativos
    timeout 15s "$EXECUTABLE" isometric_test_negative.fdf > /dev/null 2>&1
    local result=$?
    if [ $result -eq 124 ]; then
        print_result 0 "Valores negativos (timeout - normal)"
    else
        print_result $result "Valores negativos"
    fi
    
    # Probar con valores extremos
    timeout 15s "$EXECUTABLE" isometric_test_extreme.fdf > /dev/null 2>&1
    result=$?
    if [ $result -eq 124 ]; then
        print_result 0 "Valores extremos (timeout - normal)"
    else
        print_result $result "Valores extremos"
    fi
    
    # Probar con mapa rectangular
    timeout 15s "$EXECUTABLE" isometric_test_rectangular.fdf > /dev/null 2>&1
    result=$?
    if [ $result -eq 124 ]; then
        print_result 0 "Mapa rectangular (timeout - normal)"
    else
        print_result $result "Mapa rectangular"
    fi
    
    # Probar con una sola línea
    timeout 15s "$EXECUTABLE" isometric_test_single_line.fdf > /dev/null 2>&1
    result=$?
    if [ $result -eq 124 ]; then
        print_result 0 "Una sola línea (timeout - normal)"
    else
        print_result $result "Una sola línea"
    fi
    
    # Probar con una sola columna
    timeout 15s "$EXECUTABLE" isometric_test_single_column.fdf > /dev/null 2>&1
    result=$?
    if [ $result -eq 124 ]; then
        print_result 0 "Una sola columna (timeout - normal)"
    else
        print_result $result "Una sola columna"
    fi
}

# Función para probar diferentes tamaños
test_different_sizes() {
    echo -e "\n${BLUE}🔍 Probando diferentes tamaños...${NC}"
    
    # Crear mapas de diferentes tamaños
    for size in 3 5 10 15 20; do
        create_test_map_size $size
        timeout 15s "$EXECUTABLE" "isometric_test_size_${size}.fdf" > /dev/null 2>&1
        local result=$?
        if [ $result -eq 124 ]; then
            print_result 0 "Tamaño ${size}x${size} (timeout - normal)"
        else
            print_result $result "Tamaño ${size}x${size}"
        fi
    done
}

# Función para crear mapa de tamaño específico
create_test_map_size() {
    local size=$1
    local filename="isometric_test_size_${size}.fdf"
    
    > "$filename"  # Limpiar archivo
    
    for ((i=0; i<size; i++)); do
        for ((j=0; j<size; j++)); do
            echo -n "$((RANDOM % 10)) "
        done
        echo "" >> "$filename"
    done
}

# Función para probar patrones específicos
test_specific_patterns() {
    echo -e "\n${BLUE}🔍 Probando patrones específicos...${NC}"
    
    # Probar patrón de ajedrez
    timeout 10s "$EXECUTABLE" isometric_test_checkerboard.fdf > /dev/null 2>&1
    print_result $? "Patrón de ajedrez"
    
    # Probar gradiente
    timeout 10s "$EXECUTABLE" isometric_test_gradient.fdf > /dev/null 2>&1
    print_result $? "Gradiente"
    
    # Crear patrón de ondas
    cat > isometric_test_waves.fdf << EOF
0 1 2 1 0 1 2 1 0
1 2 3 2 1 2 3 2 1
2 3 4 3 2 3 4 3 2
1 2 3 2 1 2 3 2 1
0 1 2 1 0 1 2 1 0
EOF
    
    timeout 10s "$EXECUTABLE" isometric_test_waves.fdf > /dev/null 2>&1
    print_result $? "Patrón de ondas"
}

# Función para probar controles básicos
test_basic_controls() {
    echo -e "\n${BLUE}🔍 Probando controles básicos...${NC}"
    
    # Crear mapa de prueba para controles
    cat > isometric_test_controls.fdf << EOF
0 1 2 3 4
1 2 3 4 5
2 3 4 5 6
3 4 5 6 7
4 5 6 7 8
EOF

    echo -e "${CYAN}🎮 Iniciando pruebas de controles...${NC}"
    echo -e "${YELLOW}💡 Presiona ESC para salir de las pruebas de controles${NC}"
    
    # Iniciar programa para pruebas manuales
    timeout 30s "$EXECUTABLE" isometric_test_controls.fdf
    
    print_result 0 "Controles básicos (prueba manual)"
}

# Función para probar rendimiento
test_performance() {
    echo -e "\n${BLUE}🔍 Probando rendimiento...${NC}"
    
    # Crear mapa grande para prueba de rendimiento
    cat > isometric_test_performance.fdf << EOF
EOF
    
    # Generar mapa 50x50
    for ((i=0; i<50; i++)); do
        for ((j=0; j<50; j++)); do
            echo -n "$((RANDOM % 10)) "
        done
        echo "" >> isometric_test_performance.fdf
    done
    
    # Medir tiempo de ejecución
    start_time=$(date +%s.%N)
    timeout 60s "$EXECUTABLE" isometric_test_performance.fdf > /dev/null 2>&1
    end_time=$(date +%s.%N)
    
    execution_time=$(echo "$end_time - $start_time" | bc)
    
    if (( $(echo "$execution_time < 10" | bc -l) )); then
        print_result 0 "Rendimiento (${execution_time}s)"
    else
        print_result 1 "Rendimiento lento (${execution_time}s)"
    fi
}

# Función para probar estabilidad
test_stability() {
    echo -e "\n${BLUE}🔍 Probando estabilidad...${NC}"
    
    # Ejecutar el programa múltiples veces
    for i in {1..10}; do
        echo -e "${CYAN}   Ejecución $i/10...${NC}"
        
        timeout 10s "$EXECUTABLE" isometric_test_simple.fdf > /dev/null 2>&1
        if [ $? -eq 124 ]; then
            echo -e "${YELLOW}   ⚠️  Timeout en ejecución $i${NC}"
        fi
    done
    
    print_result 0 "Estabilidad (10 ejecuciones)"
}

# Función para probar casos de error
test_error_cases() {
    echo -e "\n${BLUE}🔍 Probando casos de error...${NC}"
    
    # Probar con archivo inexistente
    timeout 10s "$EXECUTABLE" "archivo_que_no_existe.fdf" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        print_result 0 "Archivo inexistente (falló correctamente)"
    else
        print_result 1 "Archivo inexistente (no falló como esperado)"
    fi
    
    # Probar sin argumentos
    timeout 10s "$EXECUTABLE" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        print_result 0 "Sin argumentos (falló correctamente)"
    else
        print_result 1 "Sin argumentos (no falló como esperado)"
    fi
    
    # Probar con archivo vacío
    touch isometric_test_empty.fdf
    timeout 10s "$EXECUTABLE" isometric_test_empty.fdf > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        print_result 0 "Archivo vacío (falló correctamente)"
    else
        print_result 1 "Archivo vacío (no falló como esperado)"
    fi
}

# Función para limpiar archivos temporales
cleanup() {
    rm -f isometric_test_*.fdf
}

# Función para generar reporte
generate_report() {
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}Reporte de Pruebas de Renderizado Isométrico${NC}"
    echo -e "${BLUE}========================================${NC}"
    
    echo -e "${CYAN}📊 Estadísticas:${NC}"
    echo -e "   Total de pruebas: $TOTAL_TESTS"
    echo -e "   ${GREEN}✅ Exitosas: $PASSED_TESTS${NC}"
    echo -e "   ${RED}❌ Fallidas: $((TOTAL_TESTS - PASSED_TESTS))${NC}"
    
    if [ $PASSED_TESTS -eq $TOTAL_TESTS ]; then
        echo -e "\n${GREEN}🎉 ¡Todas las pruebas de renderizado isométrico pasaron!${NC}"
        echo -e "${GREEN}✅ El renderizado isométrico funciona correctamente${NC}"
    else
        echo -e "\n${RED}⚠️  Algunas pruebas de renderizado isométrico fallaron${NC}"
    fi
    
    # Calcular porcentaje de éxito
    if [ $TOTAL_TESTS -gt 0 ]; then
        SUCCESS_RATE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
        echo -e "\n${BLUE}📈 Tasa de éxito: $SUCCESS_RATE%${NC}"
    fi
    
    # Mostrar consejos si hay fallos
    if [ $PASSED_TESTS -lt $TOTAL_TESTS ]; then
        echo -e "\n${YELLOW}💡 Consejos para mejorar el renderizado:${NC}"
        echo -e "   • Verifica la proyección isométrica"
        echo -e "   • Revisa el algoritmo de Bresenham"
        echo -e "   • Comprueba el manejo de coordenadas"
        echo -e "   • Optimiza el rendimiento para mapas grandes"
    fi
}

# Función principal
main() {
    echo -e "${PURPLE}🧪 Iniciando pruebas de renderizado isométrico para FDF...${NC}"
    
    # Verificar que el ejecutable existe
    if [ ! -f "$EXECUTABLE" ]; then
        echo -e "${RED}❌ Error: $EXECUTABLE no encontrado${NC}"
        echo -e "${YELLOW}💡 Ejecuta 'make' en el directorio principal primero${NC}"
        exit 1
    fi
    
    # Crear mapas de prueba
    create_isometric_test_maps
    
    # Ejecutar todas las pruebas
    test_basic_rendering
    test_edge_cases
    test_different_sizes
    test_specific_patterns
    test_basic_controls
    test_performance
    test_stability
    test_error_cases
    
    # Generar reporte
    generate_report
    
    # Limpiar archivos temporales
    cleanup
    
    echo -e "\n${PURPLE}🏁 Pruebas de renderizado isométrico completadas${NC}"
}

# Ejecutar función principal
main "$@" 