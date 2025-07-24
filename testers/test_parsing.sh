#!/bin/bash

# =============================================================================
# Test de Parsing - FDF
# =============================================================================
# Pruebas específicas para el parsing de archivos .fdf

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
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

# Función para crear mapas de prueba
create_test_maps() {
    echo -e "${CYAN}📝 Creando mapas de prueba...${NC}"
    
    # Mapa válido simple
    cat > test_simple.fdf << EOF
0 0 0
0 1 0
0 0 0
EOF

    # Mapa válido con alturas variadas
    cat > test_heights.fdf << EOF
0 1 2 3 4
1 2 3 4 5
2 3 4 5 6
3 4 5 6 7
4 5 6 7 8
EOF

    # Mapa válido grande
    cat > test_large.fdf << EOF
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

    # Mapa con valores negativos
    cat > test_negative.fdf << EOF
-2 -1 0
-1 0 1
0 1 2
EOF

    # Mapa con valores grandes
    cat > test_large_values.fdf << EOF
1000 2000 3000
2000 3000 4000
3000 4000 5000
EOF

    # Mapa rectangular (no cuadrado)
    cat > test_rectangular.fdf << EOF
0 1 2 3 4
1 2 3 4 5
EOF

    # Mapa con una sola línea
    cat > test_single_line.fdf << EOF
0 1 2 3 4 5 6 7 8 9
EOF

    # Mapa con una sola columna
    cat > test_single_column.fdf << EOF
0
1
2
3
4
EOF

    # Mapa inválido - archivo vacío
    touch test_empty.fdf

    # Mapa inválido - formato inconsistente
    cat > test_inconsistent.fdf << EOF
0 1 2
0 1
0 1 2 3
EOF

    # Mapa inválido - caracteres no numéricos
    cat > test_invalid_chars.fdf << EOF
0 a 2
1 2 3
0 1 2
EOF

    # Mapa inválido - caracteres especiales
    cat > test_special_chars.fdf << EOF
0 1 2
1 @ 3
2 3 4
EOF

    # Mapa inválido - espacios extra
    cat > test_extra_spaces.fdf << EOF
0  1  2
1  2  3
2  3  4
EOF

    # Mapa inválido - líneas vacías en medio
    cat > test_empty_lines.fdf << EOF
0 1 2

1 2 3
2 3 4
EOF

    echo -e "${GREEN}✅ Mapas de prueba creados${NC}"
}

# Función para probar mapas válidos
test_valid_maps() {
    echo -e "\n${BLUE}🔍 Probando mapas válidos...${NC}"
    
    for map in test_simple.fdf test_heights.fdf test_large.fdf test_negative.fdf \
               test_large_values.fdf test_rectangular.fdf test_single_line.fdf \
               test_single_column.fdf; do
        if [ -f "$map" ]; then
            timeout 10s "$EXECUTABLE" "$map" > /dev/null 2>&1
            print_result $? "Parsing de $map"
        fi
    done
}

# Función para probar mapas inválidos
test_invalid_maps() {
    echo -e "\n${BLUE}🔍 Probando mapas inválidos...${NC}"
    
    for map in test_empty.fdf test_inconsistent.fdf test_invalid_chars.fdf \
               test_special_chars.fdf test_extra_spaces.fdf test_empty_lines.fdf; do
        if [ -f "$map" ]; then
            timeout 10s "$EXECUTABLE" "$map" > /dev/null 2>&1
            # Debería fallar para archivos inválidos
            if [ $? -ne 0 ]; then
                print_result 0 "Parsing inválido de $map (falló correctamente)"
            else
                print_result 1 "Parsing inválido de $map (no falló como esperado)"
            fi
        fi
    done
}

# Función para probar casos edge
test_edge_cases() {
    echo -e "\n${BLUE}🔍 Probando casos edge...${NC}"
    
    # Mapa con valores muy grandes
    cat > test_very_large.fdf << EOF
999999999 999999999 999999999
999999999 999999999 999999999
999999999 999999999 999999999
EOF
    
    timeout 10s "$EXECUTABLE" test_very_large.fdf > /dev/null 2>&1
    print_result $? "Valores muy grandes"
    
    # Mapa con valores muy pequeños
    cat > test_very_small.fdf << EOF
-999999999 -999999999 -999999999
-999999999 -999999999 -999999999
-999999999 -999999999 -999999999
EOF
    
    timeout 10s "$EXECUTABLE" test_very_small.fdf > /dev/null 2>&1
    print_result $? "Valores muy pequeños"
    
    # Mapa con muchos espacios
    cat > test_many_spaces.fdf << EOF
0    1    2    3
1    2    3    4
2    3    4    5
3    4    5    6
EOF
    
    timeout 10s "$EXECUTABLE" test_many_spaces.fdf > /dev/null 2>&1
    print_result $? "Muchos espacios"
    
    # Mapa con tabs
    cat > test_with_tabs.fdf << EOF
0	1	2	3
1	2	3	4
2	3	4	5
3	4	5	6
EOF
    
    timeout 10s "$EXECUTABLE" test_with_tabs.fdf > /dev/null 2>&1
    print_result $? "Con tabs"
}

# Función para probar archivos inexistentes
test_nonexistent_files() {
    echo -e "\n${BLUE}🔍 Probando archivos inexistentes...${NC}"
    
    timeout 10s "$EXECUTABLE" "archivo_que_no_existe.fdf" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        print_result 0 "Archivo inexistente (falló correctamente)"
    else
        print_result 1 "Archivo inexistente (no falló como esperado)"
    fi
    
    timeout 10s "$EXECUTABLE" "" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        print_result 0 "Sin argumentos (falló correctamente)"
    else
        print_result 1 "Sin argumentos (no falló como esperado)"
    fi
}

# Función para probar archivos con extensión incorrecta
test_wrong_extension() {
    echo -e "\n${BLUE}🔍 Probando extensiones incorrectas...${NC}"
    
    # Crear archivo con extensión incorrecta
    cat > test_wrong_ext.txt << EOF
0 1 2
1 2 3
2 3 4
EOF
    
    timeout 10s "$EXECUTABLE" test_wrong_ext.txt > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        print_result 0 "Extensión incorrecta (falló correctamente)"
    else
        print_result 1 "Extensión incorrecta (no falló como esperado)"
    fi
}

# Función para probar archivos con permisos incorrectos
test_permission_issues() {
    echo -e "\n${BLUE}🔍 Probando problemas de permisos...${NC}"
    
    # Crear archivo sin permisos de lectura
    cat > test_no_permission.fdf << EOF
0 1 2
1 2 3
2 3 4
EOF
    
    chmod 000 test_no_permission.fdf
    
    timeout 10s "$EXECUTABLE" test_no_permission.fdf > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        print_result 0 "Sin permisos de lectura (falló correctamente)"
    else
        print_result 1 "Sin permisos de lectura (no falló como esperado)"
    fi
    
    # Restaurar permisos
    chmod 644 test_no_permission.fdf
}

# Función para limpiar archivos temporales
cleanup() {
    rm -f test_*.fdf test_*.txt
}

# Función para generar reporte
generate_report() {
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}Reporte de Pruebas de Parsing${NC}"
    echo -e "${BLUE}========================================${NC}"
    
    echo -e "${CYAN}📊 Estadísticas:${NC}"
    echo -e "   Total de pruebas: $TOTAL_TESTS"
    echo -e "   ${GREEN}✅ Exitosas: $PASSED_TESTS${NC}"
    echo -e "   ${RED}❌ Fallidas: $((TOTAL_TESTS - PASSED_TESTS))${NC}"
    
    if [ $PASSED_TESTS -eq $TOTAL_TESTS ]; then
        echo -e "\n${GREEN}🎉 ¡Todas las pruebas de parsing pasaron!${NC}"
    else
        echo -e "\n${RED}⚠️  Algunas pruebas de parsing fallaron${NC}"
    fi
    
    # Calcular porcentaje de éxito
    if [ $TOTAL_TESTS -gt 0 ]; then
        SUCCESS_RATE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
        echo -e "\n${BLUE}📈 Tasa de éxito: $SUCCESS_RATE%${NC}"
    fi
}

# Función principal
main() {
    echo -e "${CYAN}🧪 Iniciando pruebas de parsing para FDF...${NC}"
    
    # Verificar que el ejecutable existe
    if [ ! -f "$EXECUTABLE" ]; then
        echo -e "${RED}❌ Error: $EXECUTABLE no encontrado${NC}"
        echo -e "${YELLOW}💡 Ejecuta 'make' en el directorio principal primero${NC}"
        exit 1
    fi
    
    # Crear mapas de prueba
    create_test_maps
    
    # Ejecutar todas las pruebas
    test_valid_maps
    test_invalid_maps
    test_edge_cases
    test_nonexistent_files
    test_wrong_extension
    test_permission_issues
    
    # Generar reporte
    generate_report
    
    # Limpiar archivos temporales
    cleanup
    
    echo -e "\n${CYAN}🏁 Pruebas de parsing completadas${NC}"
}

# Ejecutar función principal
main "$@" 