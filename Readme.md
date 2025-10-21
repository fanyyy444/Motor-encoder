# Proyecto: Lectura de Encoder con Arduino ⚙️

Este proyecto utiliza un **Arduino** para leer un **encoder incremental** acoplado a un motor **GA25-370**.  
El código detecta la **cantidad de pulsos**, el **ángulo de giro** y la **dirección del movimiento** (Derecha o Izquierda) en tiempo real usando **interrupciones**.

## 🧠 Descripción
- Usa interrupciones para leer el **canal A** del encoder (pin 2).  
- Determina la **dirección de giro** comparando el canal A y B.  
- Calcula el **ángulo en grados** con base en los pulsos detectados.  
- Muestra los valores de pulsos, ángulo y dirección en el **Monitor Serial** cada 100 ms.

## 🧰 Conexiones
| Encoder | Arduino | Color |
|----------|----------|--------|
| Canal A  | Pin 2 (interrupción) | Amarillo |
| Canal B  | Pin 4 | Verde |
| VCC | 5 V | Rojo |
| GND | GND | Negro |

## 💾 Código
El archivo principal del proyecto es:  
`motor_encoder.ino`

Constante usada:
PULSOS_POR_REVOLUCION = 374

(11 pulsos × 34 de reducción del motor GA25-370)

## 🚀 Cómo usar
1. Conecta el encoder al Arduino según la tabla.  
2. Carga el código en tu placa.  
3. Abre el **Monitor Serial** a 9600 baudios.  
4. Gira el eje del motor y observa los valores de pulsos, ángulo y dirección.

---