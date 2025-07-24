# 🎮 Controles de FDF

## 🖱️ **Controles de Movimiento**
- **Flecha Arriba**: Mover vista hacia arriba
- **Flecha Abajo**: Mover vista hacia abajo
- **Flecha Izquierda**: Mover vista hacia la izquierda
- **Flecha Derecha**: Mover vista hacia la derecha

## 🔍 **Controles de Zoom**
- **+**: Acercar (zoom in)
- **-**: Alejar (zoom out)

## 🔄 **Controles de Rotación de Vista**
- **W**: Rotar vista en eje X (arriba)
- **S**: Rotar vista en eje X (abajo)
- **A**: Rotar vista en eje Y (izquierda)
- **D**: Rotar vista en eje Y (derecha)

## 🎯 **Controles de Rotación 3D**
- **Q**: Rotar modelo en eje Z (sentido horario)
- **E**: Rotar modelo en eje Z (sentido antihorario)

## 🔄 **Controles de Reset**
- **R**: Resetear vista a posición inicial

## 🚪 **Controles de Salida**
- **ESC**: Salir del programa

## 📊 **Información Técnica**

### Rotación 3D vs Rotación de Vista
- **Rotación de Vista (WASD)**: Cambia el ángulo de proyección isométrica
- **Rotación 3D (QE)**: Rota el modelo 3D completo en el espacio

### Colores
- Los colores se basan en la altura del terreno
- **Rojo**: Alturas altas
- **Verde**: Alturas bajas
- **Azul**: Color constante de fondo

### Proyección
- Proyección isométrica estándar
- Centrado automático del mapa
- Zoom adaptativo según el tamaño del mapa

## 🎯 **Ejemplos de Uso**

```bash
# Cargar un mapa
./fdf maps/42.fdf

# Usar controles para explorar:
# 1. Presiona R para resetear la vista
# 2. Usa las flechas para mover la vista
# 3. Usa +/- para hacer zoom
# 4. Usa Q/E para rotar el modelo 3D
# 5. Usa WASD para cambiar el ángulo de vista
# 6. Presiona ESC para salir
``` 