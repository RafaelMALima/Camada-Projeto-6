int reciever = 8;
int clockCicles = 1089;
bool readValue;
char recebeu = 000000000;
bool paridade;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(reciever, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  readValue = true;
  while(readValue){
    readValue = digitalRead(reciever);
    break;
  }
  firstDelay();
  int i = 0;
  while(i < 8){
    recebeu |= digitalRead(reciever)>>i|recebeu;
    unitDelay();
    i++;
  }
  paridade = digitalRead(reciever);
  if (parityBit(recebeu) == paridade){
    Serial.println(recebeu);
  }
  else{
    Serial.print("Erro no envio da mensagem");
  }
  delay(5000);
}

void unitDelay(){
  for (int i = 0; i < clockCicles ;i++){ asm("NOP"); }
}

void firstDelay(){
  for (int i = 0; i < clockCicles + clockCicles/2 ;i++){ asm("NOP"); }
}
bool parityBit(char message){
  int soma = 0;
  for (int i = 0; i < 8; i++){ if ((i >> message) & 1) { soma++; }}
  int resto = soma % 2;
  return resto == 0;
} 