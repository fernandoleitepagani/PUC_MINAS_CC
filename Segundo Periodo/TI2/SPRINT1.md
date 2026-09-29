# ATIVIDADE — Planejamento da Sprint 1 — EQUIPE

## Planejamento da Sprint 1 — MEDIFLOW

**Disciplina:** TI2 — 2026/2  
**Grupo:** G4  
**Integrantes:** Arthur Bicalho Angelo, Bernardo Vieira de Souza Halabi, Fernando Leite Pagani, Igor Campos Heidenreich, Lucas Morris Silva Borba e Ryan Ferreira Barros.

---

## 1. Perfis dos integrantes

- **Fernando Leite Pagani**
  - Perfil: meticuloso, organizado e detalhista. Gosta de modelagem de dados e de regras de negócio complexas.
  - Habilidades: modelagem de dados, SQL, atenção a detalhes, definição de entidades e relacionamentos.
  - Foco no projeto: cadastros com muitas regras e vínculos entre entidades.

- **Igor Campos Heidenreich**
  - Perfil: lógico, focado em backend e em validações. Prefere resolver problemas de fluxo e consistência.
  - Habilidades: lógica de programação, APIs REST, JSON Server, validações e integridade dos dados.
  - Foco no projeto: funcionalidades de CRUD com regras de consistência e status.

- **Arthur Bicalho Angelo**
  - Perfil: comunicativo, com familiaridade no domínio da saúde. Preocupado com a clareza das informações clínicas.
  - Habilidades: entendimento de domínio, UX writing, documentação, linguagem não técnica.
  - Foco no projeto: funcionalidades do médico, do prontuário e dos documentos clínicos.

- **Lucas Morris Silva Borba**
  - Perfil: criativo, com forte apelo visual e empatia pelo usuário idoso.
  - Habilidades: UI/UX, Figma, acessibilidade, usabilidade para idosos.
  - Foco no projeto: telas do paciente e experiência de uso simplificada.

- **Bernardo Vieira de Souza Halabi**
  - Perfil: analítico, gosta de relatórios e visualização de dados.
  - Habilidades: dashboards, gráficos, filtros, apresentação de informações.
  - Foco no projeto: apresentação de informações (AI) e relatórios.

- **Ryan Ferreira Barros**
  - Perfil: cauteloso, preocupado com segurança, privacidade e rastreabilidade.
  - Habilidades: autenticação, logs, controle de acesso, auditoria.
  - Foco no projeto: permissões, lembretes e log de acesso.

---

## 2. Artefatos válidos

Conforme o enunciado, os artefatos da Sprint 1 devem ser de dois tipos:

- **CI — Cadastro de Informações (CRUD):** criação, edição, exclusão e listagem de uma informação relevante para o sistema, com persistência via JSON Server.
- **AI — Apresentação de Informação:** visualização de dados já cadastrados, a partir de estruturas persistentes (JSON ou API), como relatórios, gráficos, calendários ou mapas.

Páginas puramente estáticas (HTML/CSS sem dados) **não** contam como entrega válida.

---

## 3. Planejamento da Sprint 1 — Fundação e cadastros essenciais

Foco: estrutura inicial do sistema, autenticação, cadastros básicos e as primeiras visualizações que sustentam o fluxo principal (login, cadastro, agenda e agendamento).

### A-01 — Cadastro de Usuários (Paciente, Médico e Familiar)

- **Tipo:** CI
- **Requisitos atendidos:** RF-06
- **Descrição:** CRUD completo de usuários com nome, CPF, telefone, e-mail, login, senha e perfil (paciente, médico ou familiar). O CPF não pode se repetir no sistema. Para o paciente, registrar também data de nascimento e endereço; para o médico, CRM (único) e especialidade; para o familiar, grau de parentesco. Base para todos os demais cadastros.
- **Responsável:** Arthur Bicalho Angelo

### A-02 — Cadastro de Convênios

- **Tipo:** CI
- **Requisitos atendidos:** RF-05
- **Descrição:** CRUD de convênios com nome (Unimed, UFMG, CASSI etc.) e vínculo manual do paciente ao convênio, incluindo o número da carteirinha. Sem integração automática com sistemas externos, respeitando a restrição de uso de API (RNF-03).
- **Responsável:** Lucas Morris Silva Borba

### A-03 — Cadastro de Agenda Médica

- **Tipo:** CI
- **Requisitos atendidos:** RF-01, RF-02
- **Descrição:** CRUD dos horários do médico, com data, hora de início, hora de fim e status (disponível, bloqueado ou ocupado). O médico pode definir seus horários de atendimento e bloquear períodos como férias e congressos, informando o motivo. Não pode haver dois horários ocupados no mesmo intervalo para o mesmo médico.
- **Responsável:** Bernardo Vieira de Souza Halabi

### A-04 — Cadastro de Permissões de Acesso

- **Tipo:** CI
- **Requisitos atendidos:** RF-10, RNF-02
- **Descrição:** CRUD das permissões concedidas a familiares, com tipo de permissão (agendar, cancelar, consultar lembretes ou ver resultados), status (ativa ou revogada), data de concessão e data de revogação. Uma permissão revogada deixa de valer, mas permanece registrada. Um familiar pode ter permissão para mais de um paciente.
- **Responsável:** Ryan Ferreira Barros

### A-05 — Apresentação de Horários Disponíveis

- **Tipo:** AI
- **Requisitos atendidos:** RF-07
- **Descrição:** Tela que lista, a partir do JSON Server, os horários disponíveis do médico, com filtros por data e especialidade. Voltada para o paciente idoso, com fontes ampliadas e poucos cliques, atendendo ao RNF-01 (Usabilidade e Acessibilidade).
- **Responsável:** Igor Campos Heidenreich

### A-06 — Cadastro de Consultas

- **Tipo:** CI
- **Requisitos atendidos:** RF-08, RF-09, RF-10
- **Descrição:** CRUD de consultas com status (agendada, confirmada, cancelada, remarcada ou realizada), vínculo com paciente, médico, agenda e convênio utilizado, e registro de quem criou a consulta (paciente ou familiar autorizado). O sistema deve impedir consultas em horários bloqueados, ocupados ou já passados, e manter o histórico em cancelamentos e remarcações. Respeita o escopo do projeto (RNF-04), pois apenas gerencia informações.
- **Responsável:** Fernando Leite Pagani

### A-07 — Relatório de Pacientes e Atendimentos por Convênio

- **Tipo:** AI
- **Requisitos atendidos:** RF-05
- **Descrição:** Tela que apresenta, a partir dos dados cadastrados no JSON Server, pacientes e atendimentos filtrados por convênio, apoiando a médica na organização por convênio. Complementa o Cadastro de Convênios (A-02) com a visualização das informações.
- **Responsável:** Lucas Morris Silva Borba

---

## 4. Justificativa da distribuição

- **Arthur** ficou com o cadastro de usuários por exigir maior rigor de modelagem e consistência (CPF único, múltiplos perfis), aproveitando seu perfil meticuloso e detalhista.
- **Bernardo** assumiu a agenda médica por envolver validações de horários, status e integridade dos dados, alinhadas ao seu perfil lógico e focado em backend.
- **Fernando** ficou com o cadastro de consultas por sua familiaridade com o domínio da saúde e com a clareza das informações clínicas e administrativas.
- **Igor** assumiu a apresentação de horários disponíveis por seu foco em UI/UX, acessibilidade e usabilidade para o público idoso.
- **Lucas** concentrou o cadastro de convênios e o relatório de pacientes/atendimentos por convênio, aproveitando sua habilidade analítica e de organização de informações.
- **Ryan** ficou responsável pelas permissões de acesso, alinhadas ao seu perfil cauteloso e ao RNF-02 (Segurança e Privacidade).

Dessa forma, a Sprint 1 combina **5 artefatos de Cadastro (CI)** e **2 de Apresentação (AI)**, garantindo que cada integrante contribua com pelo menos um artefato e que a base do MEDIFLOW esteja implementada e pronta para as próximas sprints.

