// --- Configuración del Encoder ---
const int encoderCanalA = 2; // Pin de interrupción (amarillo)
const int encoderCanalB = 4; // Pin de referencia (verde)

// Valor para el motor GA25-370 (11 PPR * 34 de reducción = 374)
const int PULSOS_POR_REVOLUCION = 374; 

// --- Variables Globales ---
// 'volatile' es necesario para variables que se modifican dentro de una interrupción
volatile long contadorPulsos = 0;
volatile int direccionCodigo = 0; // 0=Detenido, 1=Derecha, -1=Izquierda
volatile int estadoCanalA_Anterior;

void setup() {
  Serial.begin(9600);
  Serial.println("Prueba de Encoder - Version Fluida y Optimizada");

  pinMode(encoderCanalA, INPUT_PULLUP);
  pinMode(encoderCanalB, INPUT_PULLUP);

  // Guardamos el estado inicial para la primera comparación en la interrupción
  estadoCanalA_Anterior = digitalRead(encoderCanalA);

  // Usamos CHANGE para capturar el doble de pulsos y tener una respuesta más suave
  attachInterrupt(digitalPinToInterrupt(encoderCanalA), leerEncoder, CHANGE);
}

void loop() {
  long pulsosActuales;
  int direccionActual;

  // Copiamos los datos volátiles a variables locales de forma segura
  noInterrupts();
  pulsosActuales = contadorPulsos;
  direccionActual = direccionCodigo;
  interrupts();

  // Realizamos todos los cálculos y la lógica de visualización en cada ciclo
  float angulo = (float)pulsosActuales / PULSOS_POR_REVOLUCION * 360.0;
  
  String textoDireccion;
  if (direccionActual == 1) {
    textoDireccion = "Derecha";
  } else if (direccionActual == -1) {
    textoDireccion = "Izquierda";
  } else {
    textoDireccion = "Detenido";
  }

  // Imprimimos el estado actual en el monitor
  Serial.print("Pulsos: ");
  Serial.print(pulsosActuales);
  Serial.print(" | Angulo: ");
  Serial.print(angulo, 2); // Mostramos el ángulo con 2 decimales
  Serial.print(" grados");
  Serial.print(" | Direccion: ");
  Serial.println(textoDireccion);

  // Este delay controla la fluidez. Un valor más bajo actualiza más rápido.
  delay(100); 
}

// --- Función de Interrupción del Encoder (ISR) ---
// Esta función es súper rápida, ideal para no perder pulsos.
void leerEncoder() {
  int estadoCanalA = digitalRead(encoderCanalA);

  // Nos aseguramos de que el estado realmente ha cambiado
  if (estadoCanalA != estadoCanalA_Anterior) {
    // La lógica de cuadratura determina la dirección
    if (digitalRead(encoderCanalB) != estadoCanalA) {
      contadorPulsos++;
      direccionCodigo = 1; // Derecha
    } else {
      contadorPulsos--;
      direccionCodigo = -1; // Izquierda
    }
  }
  // Actualizamos el estado para la próxima interrupción
  estadoCanalA_Anterior = estadoCanalA;
}