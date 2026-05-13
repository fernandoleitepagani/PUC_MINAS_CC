# To‑Do List — Atividade Prática: Desafio do Desativador de Bombas
- [ ] **Configurar hardware**
  - [ ] Conectar Multi-function Shield ao Arduino  
  - [ ] Verificar ligação de S1, S2, S3, potenciômetro, 4 LEDs, buzzer e display de 7 segmentos  
  - [ ] Testar leitura analógica do potenciômetro e saída para display/buzzer

- [ ] **Ler e mapear tempo inicial**
  - [ ] Ler valor do trimpot na inicialização  
  - [ ] Mapear para intervalo **10–90 segundos**  
  - [ ] Mostrar tempo mapeado no display de 7 segmentos

- [ ] **Gerar senha aleatória**
  - [ ] Ao reset, inicializar gerador de números aleatórios (seed)  
  - [ ] Gerar sequência de **8** valores entre **1** e **3**  
  - [ ] Armazenar sequência em buffer interno

- [ ] **Preparar lógica de início**
  - [ ] Aguardar primeiro pressionamento de qualquer botão (S1/S2/S3)  
  - [ ] Ao primeiro pressionamento, exibir **"GO"** brevemente no display  
  - [ ] Iniciar contagem regressiva a partir do tempo mapeado

- [ ] **Implementar leitura de botões e verificação de sequência**
  - [ ] Detectar pressionamentos (com debounce)  
  - [ ] Comparar cada entrada com o valor esperado na sequência  
  - [ ] Incrementar contador de acertos por tentativa quando correto  
  - [ ] Atualizar LEDs em formato binário mostrando acertos acumulados na tentativa atual

- [ ] **Lidar com erro na sequência**
  - [ ] Ao erro, reiniciar índice da tentativa (voltar ao início da sequência atual)  
  - [ ] Aumentar velocidade do cronômetro em **5%** (ajustar frequência de atualização do timer)  
  - [ ] Manter feedback visual dos LEDs

- [X] **Temporização e alarmes sonoros**
  - [X] Calcular limiar de **10%** do tempo inicial  
  - [X] Quando tempo ≤ 10% do inicial, buzzer bip curto a cada **1 s**  
  - [X] Se tempo = 0: buzzer contínuo e display travado em **"0000"**

- [ ] **Condição de sucesso**
  - [ ] Se 8 valores forem inseridos corretamente: parar contador  
  - [ ] Exibir **"OFF"** no display  
  - [ ] Emitir **3 bipes** de confirmação pelo buzzer

- [ ] **Sincronização / reinício (opcional)**
  - [ ] Permitir reinício manual (botão dedicado ou reset)  
  - [ ] Restaurar tempo e gerar nova sequência ao reiniciar

- [ ] **Testes e validação**
  - [ ] Testar vários tempos do potenciômetro (10–90 s)  
  - [ ] Testar todas as sequências geradas aleatoriamente  
  - [ ] Testar comportamento em erro (velocidade + LEDs)  
  - [ ] Testar alertas de 10% e Game Over  
  - [ ] Testar confirmação de sucesso (OFF + 3 bipes)

- [ ] **Documentação e código**
  - [ ] Comentar funções principais (inicialização, leitura, verificação, timer, alarms)  
  - [ ] Incluir instruções de uso e esquema de conexões  
  - [ ] Incluir sugestão de ajustes (debounce, taxa de aumento de 5%)

