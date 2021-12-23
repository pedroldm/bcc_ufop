Avaliação 2 de Programação Funcional

Aluno: Pedro Lucas Damasceno Silva
Matrícula: 20.1.4003
Observação: o seguinte erro se apresentou durante a tentativa de execução do comando 'stack build':
            import qualified System.Console.MinTTY.Win32 as Win32 (isMinTTY, isMinTTYHandle)
            para solucioná-lo, encontrei uma flag e a adicionei ao arquivo 'stack.yaml'.
Fonte: https://stackoverflow.com/questions/70045586/could-not-find-module-system-console-mintty-win32-when-compiling-test-framework

========================

ATENÇÃO
-------

* A interpretação dos enunciados faz parte
da avaliação.

* A avaliação deve ser resolvida INDIVIDUALMENTE.
Plágios não serão tolerados. TODAS as avaliações
em que algum tipo de plágio for detectado receberão
nota ZERO.

* Se você utilizar recursos disponíveis na internet
e que não fazem parte da bibliografia, você deverá
explicitamente citar a fonte apresentando o link
pertinente como um comentário em seu código.

* Todo código produzido por você deve ser acompanhado
por um texto explicando a estratégia usada para a
solução. Lembre-se: meramente parafrasear o código
não é considerado uma explicação!

* Não é permitido eliminar a diretiva de compilação -Wall
do cabeçalho desta avaliação.

* Caso julgue necessário, você poderá incluir bibliotecas
adicionais incluindo "imports" no cabeçalho deste
módulo.

* Seu código deve ser compilado sem erros e warnings
de compilação. A presença de erros acarretará em
uma penalidade de 20% para cada erro de compilação e
de 10% para cada warning. Esses valores serão descontados
sobre a nota final obtida pelo aluno.

* Todo o código a ser produzido por você está marcado
usando a função "undefined". Sua solução deverá
substituir a chamada a undefined por uma implementação
apropriada.

* Todas as questões desta avaliação possuem casos de
teste para ajudar no entendimento do resultado
esperado. Para execução dos casos de teste, basta
executar os seguintes comandos:

```
$> stack build
$> stack exec prova02-exe
```

* Sobre a entrega da solução:

1. A entrega da solução da avaliação deve ser feita
como um único arquivo .zip contendo todo o projeto
stack usado.

2. O arquivo .zip a ser entregue deve usar a seguinte
convenção de nome: MATRÍCULA.zip, em que matrícula é
a sua matrícula. Exemplo: Se sua matrícula for
20.1.2020 então o arquivo entregue deve ser
2012020.zip. A não observância ao critério de nome e
formato da solução receberá uma penalidade de 20%
sobre a nota obtida na avaliação.

3. O arquivo de solução deverá ser entregue usando a
atividade "Entrega da Avaliação 2" no Moodle dentro do
prazo estabelecido.

4. É de responsabilidade do aluno a entrega da solução
dentro deste prazo.

5. Sob NENHUMA hipótese serão aceitas soluções fora do
prazo ou entregues usando outra ferramenta que
não a plataforma Moodle.


Setup inicial
-------------

> {-# OPTIONS_GHC -Wall #-}

> module Main where

> import ParseLib
> import Test.Tasty
> import Test.Tasty.HUnit

> main :: IO ()
> main = defaultMain tests

> tests :: TestTree
> tests
>   = testGroup "Unit tests"
>         [
>            question01aTests
>         ,  question01bTests
>         ,  question02aTests
>         ,  question02bTests
>         ,  question03aTests
>         ,  question03bTests
>         ]

> parse :: Parser s a -> [s] -> Maybe a
> parse p s = if null res then Nothing
>             else Just $ fst (head res)
>      where
>        res = runParser p s

Turtle-oriented programming
===========================

Introdução
-----------

Nesta avaliação, você deverá implementar um conjunto de funções para realizar o parsing de
uma pequena linguagem de programação para movimentar uma tartaruga em um plano 2D.

Desenvolvimento do parser
-------------------------

Questão 1. Nessa questão desenvolveremos um conjunto de funções para
realizar o parsing de uma posição da tartaruga no plano. Posições são
representadas pelo seguinte tipo:

> data Position
>       = Position {
>            x :: Int
>         ,  y :: Int
>         } deriving (Eq, Ord, Show)

que representa as coordenadas da tartaruga no plano cartesiano.

a) Desenvolva o parser:

{- Utilizei o parser whitespace para tratar casos onde haja espaço anterior ao número. Os posteriores são indiferentes
   e eu desconsiderei. Em seguida, considero apenas o retorno do parser natural, que retorna um Int conforme a definição
   de tipos de parseNumber. -}

> parseNumber :: Parser Char Int
> parseNumber = f <$> whitespace <*> natural <*> whitespace
>   where
>       f _ a _ = a

que processa números inteiros descartando espaços antes e depois da
string processada. Sua implementação deve satisfazer os seguintes
casos de teste.

> question01aTests :: TestTree
> question01aTests
>       = testGroup "Question 01-a Tests"
>                    [
>                       testCase "Question 01-a success" $
>                           parse parseNumber "11" @?= Just 11
>                    ,  testCase "Question 01-a success spaces right" $
>                           parse parseNumber "11 " @?= Just 11
>                    ,  testCase "Question 01-a success spaces left" $
>                           parse parseNumber " 11" @?= Just 11
>                    ,  testCase "Question 01-a success spaces both" $
>                           parse parseNumber "  11  " @?= Just 11
>                    ,  testCase "Question 01-a failure no number" $
>                           parse parseNumber "abc" @?= Nothing
>                    ,  testCase "Question 01-a failure empty" $
>                           parse parseNumber "" @?= Nothing
>                    ]

b) Desenvolva a função

{- Resolução similar à questão 1-a, com a repetição de parsers e a utilização do construtor de Position
   para retornar o tipo referido. -}

> parsePosition :: Parser Char Position
> parsePosition = f <$> whitespace <*> natural <*> whitespace <*> natural <*> whitespace
>   where
>       f _ a _ b _ = Position a b

que realiza o processamento de uma posição da tartaruga no plano.
Uma posição é representada por um par de números naturais separados
por um ou mais espaços em branco. Sua implementação deve satisfazer
os seguintes casos de teste.

> question01bTests :: TestTree
> question01bTests
>       = testGroup "Question 01-b Tests"
>                    [
>                       testCase "Question 01-b success" $
>                           parse parsePosition "11 22" @?= Just (Position 11 22)
>                    ,  testCase "Question 01-b success spaces right" $
>                           parse parsePosition "11 22  " @?= Just (Position 11 22)
>                    ,  testCase "Question 01-b success spaces left" $
>                           parse parsePosition " 11 22" @?= Just (Position 11 22)
>                    ,  testCase "Question 01-b success spaces both" $
>                           parse parsePosition "  11 22 " @?= Just (Position 11 22)
>                    ,  testCase "Question 01-b failure no number" $
>                           parse parsePosition "abc" @?= Nothing
>                    ,  testCase "Question 01-b failure empty" $
>                           parse parsePosition "" @?= Nothing
>                    ]

Questão 2. Nesta questão desenvolveremos um conjunto de funções para
implementar um parsing do estado inicial da tartaruga no plano que é
representado pelo seguinte tipo.

> data Turtle
>       = Turtle {
>           position :: Position
>         , facing   :: Facing
>         } deriving (Eq, Ord, Show)

O tipo `Facing` denota qual a direção em que a tartaruga está caminhando no plano.

> data Facing = North | South | East | West deriving (Eq, Ord, Show)

2-a) Desenvolva a função

{- Associa o parser whitespace sequencialmente (<*>) aos symbol de cada possibilidade de coordenada através de <|>, que 
   dispensa a execução dos subsequentes caso algum tenha sucesso e não retorne []. Por fim, é chamada a função que compara o caractere
   e retorna o tipo Facing correspondente. -}

> parseFacing :: Parser Char Facing
> parseFacing = f <$> whitespace <*> (symbol 'N' <|> symbol 'S' <|> symbol 'E' <|> symbol 'W') <*> whitespace
>  where
>     f _ a _ = getCoordinate a

{- Implementei essa função dada a necessidade de determinar a coordenada novamente nas questões posteriores. Como Haskell
   não admite funções sem retorno (if sem else, guardas sem otherwise), elaborei um tratamento de error para contornar o warning
   decorrente desse fato mas que, da forma como parseFacing foi implementado, nunca será acionado. -}

> getCoordinate :: Char -> Facing
> getCoordinate a
>  | a == 'N' = North
>  | a == 'S' = South
>  | a == 'E' = East
>  | a == 'W' = West
>  | otherwise = error "Coordenada inválida"

que realiza o parsing de uma representação da direção da tartaruga. Representaremos
a posição `North` pelo caractere `N`, `South` por `S`, `East` por `E` e `West` por
`W`. Sua função deve satisfazer os seguintes casos de teste:

> question02aTests :: TestTree
> question02aTests
>       = testGroup "Question 02-a Tests"
>                    [
>                       testCase "Question 02-a success" $
>                           parse parseFacing "N" @?= Just North
>                    ,  testCase "Question 02-a success spaces right" $
>                           parse parseFacing "N  " @?= Just North
>                    ,  testCase "Question 02-a success spaces left" $
>                           parse parseFacing " N" @?= Just North
>                    ,  testCase "Question 02-a success spaces both" $
>                           parse parseFacing "  N " @?= Just North
>                    ,  testCase "Question 02-a failure invalid char" $
>                           parse parseFacing "1bc" @?= Nothing
>                    ,  testCase "Question 02-a failure empty" $
>                           parse parseFacing "" @?= Nothing
>                    ]

2-b) Desenvolva a função

{- Parse construído na ordem explícita nos casos de teste. Em seguida, Turtle é construído de acordo com seus tipos e construtor -}

> parseTurtle :: Parser Char Turtle
> parseTurtle = f <$> whitespace <*> natural <*> whitespace <*> natural <*> whitespace <*> (symbol 'N' <|> symbol 'S' <|> symbol 'E' <|> symbol 'W') <*> whitespace
>     where
>         f _ a _ b _ c _ = Turtle (Position a b) (getCoordinate c)

que processa o estado inicial de uma tartaruga no plano de execução da linguagem
turtle. Sua função deve atender os seguintes casos de teste:

> tur :: Maybe Turtle
> tur = Just (Turtle (Position 11 22) North)

> question02bTests :: TestTree
> question02bTests
>       = testGroup "Question 02-b Tests"
>                    [
>                       testCase "Question 02-b success" $
>                           parse parseTurtle "11 22 N" @?= tur
>                    ,  testCase "Question 02-b success spaces right" $
>                           parse parseTurtle "11 22 N  " @?= tur
>                    ,  testCase "Question 02-b success spaces left" $
>                           parse parseTurtle " 11 22 N" @?= tur
>                    ,  testCase "Question 02-b success spaces both" $
>                           parse parseTurtle "  11 22 N " @?= tur
>                    ,  testCase "Question 02-b failure invalid char" $
>                           parse parseTurtle "a 11 bc" @?= Nothing
>                    ,  testCase "Question 02-b failure empty" $
>                           parse parseTurtle "" @?= Nothing
>                    ]

Questão 3. O objetivo desta questão é o desenvolvimento de um conjunto de funções para fazer o parsing
de programas da linguagem turtle.

3-a) Instruções da linguagem turtle são representadas pelo seguinte tipo de dados:

> data Instr
>    = Forward | ToLeft | ToRight | Print
>      deriving (Eq, Ord, Show)

Desenvolva a função

{- Resolução similar à questão 2-a, utilizando a mesma associação de parsers, diferenciando apenas nas possibilidades de instruções
   passadas a symbol. -}

> parseInstr :: Parser Char Instr
> parseInstr = f <$> whitespace <*> (symbol 'F' <|> symbol 'L' <|> symbol 'R' <|> symbol 'P') <*> whitespace
>     where
>        f _ a _ = getInstruction a

{- Função similar à desenvolvida na questão 2-a. Utilização da mensagem de erro em 'otherwise' está justificada no comentário da questão citada. -}

> getInstruction :: Char -> Instr
> getInstruction a
>  | a == 'F' = Forward
>  | a == 'L' = ToLeft
>  | a == 'R' = ToRight
>  | a == 'P' = Print
>  | otherwise = error "Instrução inválida"

que realiza o parsing de uma instrução turtle. Cada instrução é representada por uma letra, como se
segue: `Forward` é representada pela letra `F`, `ToLeft` por `L`, `ToRight` por `R` e `Print` por `P`.
Seu parser deve satisfazer os seguintes casos de teste.

> question03aTests :: TestTree
> question03aTests
>       = testGroup "Question 03-a Tests"
>                    [
>                       testCase "Question 03-a success" $
>                           parse parseInstr "F" @?= Just Forward
>                    ,  testCase "Question 03-a success spaces right" $
>                           parse parseInstr "F" @?= Just Forward
>                    ,  testCase "Question 03-a success spaces left" $
>                           parse parseInstr " F" @?= Just Forward
>                    ,  testCase "Question 03-a success spaces both" $
>                           parse parseInstr "  F " @?= Just Forward
>                    ,  testCase "Question 03-a failure invalid char" $
>                           parse parseInstr "a 11 bc" @?= Nothing
>                    ,  testCase "Question 03-a failure empty" $
>                           parse parseInstr "" @?= Nothing
>                    ]

3-b) Programas completos da linguagem turtle são expressos pela configuração inicial
da tartaruga no plano e lista de instruções a serem executadas. O tipo `Program`
representa programas turtle:

> data Program
>       = Program {
>           start :: Turtle
>         , code  :: [Instr]
>         } deriving (Eq, Ord, Show)

O campo `start` representa a posição inicial e code a lista de instruções que deve ser executada.
Com base no apresentado, implemente a função:

{- Utilizei os parsers de Turtle e Instr (associado ao parser many para percorrer a lista de instruções) desenvolvidos nas questões
   anteriores. Por fim, o retorno dos parsers é utilizado na construção de Program. Preocupado com a criação correta da lista de 
   instruções, executei o parser manualmente e observei o seguinte resultado:

   (Program {start = Turtle {position = Position {x = 11, y = 22}, facing = North}, code = [Forward,ToLeft,Forward,Forward]},"")

   E observei que, da forma como many e parseInstr estão implementados, a lista de instruções é criada corretamente sem a necessidade de
   acumulador, e, portanto, mantive como está. -}

> parseProgram :: Parser Char Program
> parseProgram = f <$> parseTurtle <*> many parseInstr <*> whitespace
>     where
>         f a b _ = Program a b

para realizar o parsing de programas turtle. Seu parser deve atender os seguintes casos de teste.

> prog :: Program
> prog = Program (Turtle (Position 11 22) North)
>                [Forward, ToLeft, Forward, Forward]

> question03bTests :: TestTree
> question03bTests
>       = testGroup "Question 03-b Tests"
>                    [
>                       testCase "Question 03-b success" $
>                           parse parseProgram "11 22 N FLFF" @?= Just prog
>                    ,  testCase "Question 03-b success spaces right" $
>                           parse parseProgram "11 22 N FLFF  " @?= Just prog
>                    ,  testCase "Question 03-b success spaces left" $
>                           parse parseProgram " 11 22 N FLFF" @?= Just prog
>                    ,  testCase "Question 03-b success spaces both" $
>                           parse parseProgram "  11 22 N FLFF  " @?= Just prog
>                    ,  testCase "Question 03-b failure invalid char" $
>                           parse parseProgram "b 11 bc" @?= Nothing
>                    ,  testCase "Question 03-b failure empty" $
>                           parse parseProgram "" @?= Nothing
>                    ]