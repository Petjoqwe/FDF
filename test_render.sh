#!/bin/bash

echo "=== FDF Render Test ==="
echo "Testing different maps..."

# Lista de mapas para probar
maps=("maps/simple.fdf" "maps/42.fdf" "maps/test1.fdf" "maps/test2.fdf" "maps/test3.fdf")

for map in "${maps[@]}"; do
    echo ""
    echo "Testing: $map"
    echo "Map dimensions and content:"
    
    # Mostrar información del mapa
    if [ -f "$map" ]; then
        echo "File exists: ✓"
        echo "First few lines:"
        head -5 "$map"
        echo "..."
        echo "Total lines: $(wc -l < "$map")"
        
        # Probar el parser
        echo ""
        echo "Parser test:"
        timeout 5s ./fdf "$map" 2>&1 | head -10
        
        echo "----------------------------------------"
    else
        echo "File not found: ✗"
    fi
done

echo ""
echo "=== Render Test Complete ==="
echo ""
echo "🎮 CONTROLES DISPONIBLES:"
echo "📱 Movimiento: Flechas"
echo "🔍 Zoom: +/-"
echo "🔄 Rotación Vista: WASD"
echo "🎯 Rotación 3D: Q/E"
echo "🔄 Reset: R"
echo "🚪 Salir: ESC"
echo ""
echo "Para ver el renderizado 3D en un entorno gráfico:"
echo "1. Run: ./fdf maps/42.fdf"
echo "2. Usa Q/E para rotar el modelo 3D"
echo "3. Usa WASD para cambiar el ángulo de vista"
echo "4. Usa flechas para mover la vista"
echo "5. Usa +/- para zoom"
echo "6. Presiona R para resetear"
echo "7. Presiona ESC para salir" 