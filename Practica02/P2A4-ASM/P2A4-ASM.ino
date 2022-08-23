void setup()
{
  DDRB = DDRB | B10000000; // Data Direction Register B: Inputs 0-6, Output 7
}

void loop()
{
  asm (
    "inicio: \n\t" // Define un punto en la memoria llamado inicio
    "sbi 0x05,0x07 \n\t" // Define el bit 7 en el puerto 5 (registro I/O)
    "call tiempo \n\t" // Llama la subrutina tiempo definida a continuación
    "cbi 0x05,0x07 \n\t" // Hace clear el bit 7 en el puerto 5 (registro I/O)
    "call tiempo \n\t" // Llama la subrutina tiempo definida a continuación
    "jmp main \n\t" // Salta al lugar en la memoria con el nombre main

    "tiempo: \n\t" // Define un punto en la memoria llamado tiempo
    "LDI r22, 45 \n\t" // Cargar inmediatamente 45 en el registro r22
    "LOOP_3: \n\t" // Define punto en la memoria llamado LOOP_3
    "LDI r21, 255 \n\t" // Cargar inmediatamente 255 en el registro r21
    "LOOP_2: \n\t" // Define punto en la memoria llamado LOOP_2
    "LDI r20, 255 \n\t" // Cargar inmediatamente 255 en el registro r20
    "LOOP_1: \n\t" // Define punto en la memoria llamado LOOP_1
    "DEC r20 \n\t" // Decrementa el valor del registro r20 por uno
    "BRNE LOOP_1 \n\t" // Si r20 es 0 entonces se mueve al punto LOOP_1
    "DEC r21 \n\t" // Decrementa el valor del registro r21 por uno
    "BRNE LOOP_2 \n\t" // Si r21 es 0 entonces se mueve al punto LOOP_2
    "DEC r22 \n\t" // Decrementa el valor del registro r22 por uno
    "BRNE LOOP_3 \n\t" // Si r22 es 0 entonces se mueve al punto LOOP_3
    "ret \n\t" // Regresa de la subrutina llamada
  );
}
