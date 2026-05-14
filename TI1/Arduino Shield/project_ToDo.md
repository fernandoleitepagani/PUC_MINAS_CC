# To‑Do List — Atividade Prática: Desafio do Desativador de Bombas
_Checar manual [Shield Arduino](https://blog.eletrogate.com/guia-completo-do-shield-multi-funcoes-para-arduino/)_
- [X] **Ler e mapear tempo inicial**
  - [X] Ler valor do trimpot na inicialização  
  - [X] Mapear para intervalo **10–90 segundos**  
  - [X] Mostrar tempo mapeado no display de 7 segmentos

- [X] **Gerar senha aleatória**
  - [X] Ao reset, inicializar gerador de números aleatórios (seed)  
  - [X] Gerar sequência de **8** valores entre **1** e **3**  
  - [X] Armazenar sequência em buffer interno

- [ ] **Preparar lógica de início**
  - [X] Aguardar primeiro pressionamento de qualquer botão (S1/S2/S3)  
  - [X] Ao primeiro pressionamento, exibir **"GO"** brevemente no display  
  - [X] Iniciar contagem regressiva a partir do tempo mapeado

- [ ] **Implementar leitura de botões e verificação de sequência**   <------
  - [ ] Detectar pressionamentos
  - [ ] Função chegar senha
  - [ ] Função got_right_wrong
  - [ ] Comparar cada entrada com o valor esperado na sequência  
  - [X] Incrementar contador de acertos por tentativa quando correto  
  - [X] Atualizar LEDs em formato binário mostrando acertos acumulados na tentativa atual
    - [ ] Definir pinos dos LEDs

- [X] **Lidar com erro na sequência**
  - [X] Ao erro, reiniciar índice da tentativa (voltar ao início da sequência atual)  
  - [ ] Aumentar velocidade do cronômetro em **5%** (ajustar frequência de atualização do timer)  
  - [X] Manter feedback visual dos LEDs

- [X] **Temporização e alarmes sonoros**
  - [X] Calcular limiar de **10%** do tempo inicial  
  - [X] Quando tempo ≤ 10% do inicial, buzzer bip curto a cada **1 s**  
  - [X] Se tempo = 0: buzzer contínuo e display travado em **"0000"**

- [X] **Condição de sucesso**
  - [X] Se 8 valores forem inseridos corretamente: parar contador  
  - [X] Exibir **"OFF"** no display  
  - [X] Emitir **3 bipes** de confirmação pelo buzzer

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
