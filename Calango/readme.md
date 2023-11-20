# Boleto de Condomínio em Calango

**Síntese:**
O algoritmo "BoletoCondominio" foi desenvolvido com o objetivo de calcular a taxa de condomínio com base no bloco do apartamento e no mês de referência. Este programa foi implementado nas linguagens Calango, proporcionando uma solução eficaz para o cálculo do valor do boleto de condomínio.

**Instruções de Uso:**
1. **Entrada de Dados:**
   - O usuário é solicitado a fornecer o número do apartamento (variando de 1 a 50) e o mês de referência (valores de 1 a 12).
   - Os dados são confirmados, e o programa identifica o bloco correspondente ao apartamento.

2. **Processamento:**
   - O programa utiliza estruturas condicionais para determinar o bloco do apartamento e o mês de referência, além de calcular a taxa de condomínio.
   - A função `valorBoleto` é responsável por calcular o valor final do boleto, considerando o bloco, o mês e possíveis eventos especiais.

3. **Saída de Dados:**
   - Um boleto de condomínio é gerado na tela, exibindo informações como o mês de referência, o número do apartamento, o bloco, a data de vencimento e o valor do boleto.

**Exemplo:**
```calango
Boleto_Condominio.com

Número do apartamento: 25
Mês de referência: 6

BANCO CONDOMINIO BRASIL|+55|061

564.45512.1.215.4646.5874.31505

MÊS: junho
APARTAMENTO: 25
BLOCO: cc

VENCIMENTO DO BOLETO: julho

VALOR DO BOLETO: 600.0

|| ||||| |||||||| ||||| || ||||
```

**Observações:**
- Certifique-se de inserir valores válidos para o número do apartamento e o mês de referência.
- O programa considera diferentes taxas de condomínio para cada bloco e aplicação de acréscimos conforme o mês e eventos especiais.
- O boleto gerado exibe as informações essenciais para o pagamento.

**Desenvolvedor:**
- Jéssica Eveline
- 221022319

**Data de Conclusão:**
1.2022