#!/bin/bash

# ==========================================
#              CONFIGURAÇÕES
# ==========================================

PIPEX=./pipex
RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m'

# ==========================================
#           FUNÇÃO PADRÃO DE TESTE
# ==========================================

run_test () {
    desc=$1
    infile_content=$2
    cmd1=$3
    cmd2=$4

    infile="in_test"
    outfile="out_test"
    expected="expected_test"

    echo -e "${CYAN}TESTE: $desc${NC}"

    # cria infile
    echo -e "$infile_content" > $infile

    # roda o pipex
    $PIPEX $infile "$cmd1" "$cmd2" $outfile 2>/dev/null

    # roda o shell
    < $infile $cmd1 | $cmd2 > $expected 2>/dev/null

    # compara
    if diff -q $outfile $expected >/dev/null ; then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${RED}KO${NC}"
        echo "Diferenças:"
        diff $outfile $expected
    fi

    rm -f $infile $outfile $expected
    echo ""
}

# ==========================================
#              INÍCIO
# ==========================================

echo -e "${CYAN}"
echo "======================================="
echo "        PIPEX TESTER - RAFA            "
echo "======================================="
echo -e "${NC}"

# ==========================================
# 1. TESTES BÁSICOS
# ==========================================

run_test "Simples cat | wc" "a\nb\nc\n" "cat" "wc -l"
run_test "grep | wc" "a\nb\nb\nc\n" "grep b" "wc -l"
run_test "cut com delimitador" "10 20 30\n40 50 60\n" "cut -d\  -f2" "wc -l"

# ==========================================
# 2. CAMINHOS ABSOLUTOS
# ==========================================

run_test "Absolute paths" "oi" "/bin/cat" "/usr/bin/wc -l"

# ==========================================
# 3. CMD1 FALHA
# ==========================================

run_test "cmd1 inexistente" "oi" "comando_invalido" "wc -l"

# ==========================================
# 4. CMD2 FALHA
# ==========================================

run_test "cmd2 inexistente" "oi" "cat" "comando_invalido"

# ==========================================
# 5. ARQUIVO DE ENTRADA
# ==========================================

echo -e "${CYAN}TESTE: infile não existe${NC}"
rm -f in_test
$PIPEX in_test "cat" "wc -l" out_test 2>/dev/null
< in_test cat | wc -l > expected_test 2>/dev/null
if diff -q out_test expected_test >/dev/null ; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
fi
rm -f out_test expected_test
echo ""

# ==========================================
# 6. OUTFILE SEM PERMISSÃO
# ==========================================

echo -e "${CYAN}TESTE: outfile sem permissão${NC}"
echo oi > in_test

rm -f out_test
touch out_test
chmod 000 out_test

$PIPEX in_test "cat" "wc -l" out_test 2>/dev/null
ret=$?

if [ $ret != 0 ]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
fi

chmod 644 out_test
rm -f in_test out_test
echo ""

# ==========================================
# 7. ESPAÇOS E FLAGS
# ==========================================

run_test "grep com flags" "a\nB\nc\nA\n" "grep -i a" "wc -l"
run_test "múltiplos espaços" "um   dois   tres" "tr -s ' '" "wc -c"

# ==========================================
# 8. PIPE VAZIO
# ==========================================

run_test "arquivo vazio" "" "cat" "wc -l"

# ==========================================
# 8.1 PIPE VAZIO — TESTES AVANÇADOS
# ==========================================

run_test "arquivo vazio + cmd1 inexistente" "" "comando_invalido" "wc -l"
run_test "arquivo vazio + cmd2 inexistente" "" "cat" "comando_invalido"
run_test "arquivo vazio + sort" "" "sort" "wc -l"
run_test "arquivo vazio + echo" "" "echo oi" "wc -l"
run_test "arquivo vazio + múltiplos espaços" "" "tr -s ' '" "wc -c"

# ==========================================
# 9. STDIN E STDOUT DIFERENTES
# ==========================================

rm -f out_test expected_test

run_test "ls | wc" "ignored" "ls" "wc -l"
run_test "rev | wc" "abc" "rev" "wc -c"

# ==========================================
# 10. GRANDES QUANTIDADES DE DADOS
# ==========================================

seq 1 10000 > in_test
echo -e "${CYAN}TESTE: grande quantidade de dados${NC}"

$PIPEX in_test "cat" "wc -l" out_test
< in_test cat | wc -l > expected_test

if diff -q out_test expected_test >/dev/null ; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
fi

rm -f in_test out_test expected_test
echo ""

echo -e "${GREEN}TODOS OS TESTES FINALIZADOS${NC}"
