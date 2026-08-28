# WeatherRestAPI

Uma API REST desenvolvida com **Java e Spring Boot** para consultar e disponibilizar informações relacionadas ao clima de cidades, com um endpoint específico voltado para **Belo Horizonte, Minas Gerais**.

O projeto foi criado como uma oportunidade de praticar conceitos fundamentais do desenvolvimento backend moderno, especialmente a construção de APIs REST, integração com serviços externos e organização de uma aplicação utilizando o ecossistema Spring.

---

## Sobre o projeto

A **WeatherRestAPI** funciona como uma camada intermediária entre o cliente e APIs externas de dados meteorológicos e geográficos.

A aplicação oferece dois tipos principais de consulta:

- Consulta do clima atual de **Belo Horizonte**;
- Consulta de informações relacionadas a uma cidade informada pelo usuário.

Para isso, o projeto realiza requisições HTTP para a API **Open-Meteo**, recebe a resposta e a disponibiliza através dos próprios endpoints da aplicação.

Além de resolver um problema simples e prático, o projeto foi importante para consolidar conhecimentos sobre como aplicações backend se comunicam com serviços externos.

---

## Tecnologias e ferramentas utilizadas

- **Java**
- **Spring Boot**
- **Spring Web**
- **Maven**
- **REST API**
- **RestTemplate**
- **Open-Meteo API**
- **JUnit / Spring Boot Test**

---

## Arquitetura do projeto

O projeto foi organizado seguindo uma separação básica de responsabilidades:

```text
src/
├── main/
│   ├── java/
│   │   └── com/example/WeatherRestAPI/
│   │       ├── controller/
│   │       │   └── controller.java
│   │       ├── service/
│   │       │   └── WeatherService.java
│   │       └── WeatherRestApiApplication.java
│   │
│   └── resources/
│       └── application.properties
│
└── test/
    └── java/
        └── com/example/WeatherRestAPI/
            └── WeatherRestApiApplicationTests.java
```
## Endpoints

### Clima de Belo Horizonte

```http
GET /climaBH
```

Esse endpoint consulta uma URL configurada especificamente para obter a temperatura atual de Belo Horizonte.

Exemplo:

```text
http://localhost:8080/climaBH
```

---

### Consulta por cidade

```http
GET /clima/{cidade}
```

Esse endpoint recebe o nome de uma cidade como parâmetro.

Exemplo:

```text
http://localhost:8080/clima/Sao%20Paulo
```

A cidade informada é utilizada para realizar uma consulta através do serviço externo configurado na aplicação.

---

## Exemplos de uso

Consultar o clima de Belo Horizonte:

```bash
curl http://localhost:8080/climaBH
```

Consultar uma cidade:

```bash
curl http://localhost:8080/clima/Belo%20Horizonte
```

---

## O que aprendi com este projeto

Este projeto foi especialmente importante para transformar conhecimentos teóricos em uma aplicação backend funcional.

Durante o desenvolvimento, pude praticar e compreender melhor:

### Desenvolvimento de APIs REST

A criação dos endpoints ajudou a consolidar conceitos como:

- Rotas HTTP;
- Métodos GET;
- Parâmetros de URL;
- Comunicação entre cliente e servidor;
- Retorno de respostas HTTP.

### Integração com APIs externas

Um dos principais aprendizados foi entender como uma aplicação pode consumir dados de outros serviços através de requisições HTTP.

Isso envolveu:

- Construção de URLs dinâmicas;
- Envio de requisições;
- Recebimento de respostas;
- Verificação do status HTTP;
- Tratamento básico de falhas na comunicação.

### Organização do código

A separação entre as camadas de **Controller** e **Service** ajudou a compreender melhor o conceito de responsabilidade única.

Em vez de concentrar toda a lógica em uma única classe, cada componente possui uma função mais clara dentro da aplicação.

Esse tipo de organização facilita manutenção, leitura do código, testes, evolução do projeto.

### Configuração externa

Também pratiquei a utilização do arquivo `application.properties` para separar configurações do código-fonte.

Essa abordagem evita deixar informações de configuração espalhadas pela aplicação e torna o projeto mais flexível para futuras alterações.

---

## Por que este projeto é relevante para minha formação?

A **WeatherRestAPI** representa um passo importante no meu desenvolvimento como programador backend.

Apesar de ser um projeto focado e objetivo, ele envolve conceitos presentes em aplicações reais: **APIs REST, comunicação HTTP, integração entre serviços, configuração de aplicações e organização em camadas**.

Mais do que simplesmente consumir uma API de clima, o projeto me ajudou a entender como diferentes serviços podem se comunicar e como uma aplicação Spring Boot pode atuar como uma interface organizada entre um cliente e fontes externas de dados.

Este projeto faz parte do meu processo de aprendizado e evolução contínua como desenvolvedor, servindo como base para projetos futuros com arquiteturas, integrações e funcionalidades mais complexas.

