#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[1;33m"
BLUE="\033[0;34m"
NC="\033[0m"

echo -e "${BLUE}====================================================${NC}"
echo -e "${BLUE}      🚀 PUSH_SWAP ULTIMATE TESTER (Subject 42)      ${NC}"
echo -e "${BLUE}====================================================${NC}"

# 1. Compilation Test
echo -e "\n${YELLOW}[1/5] Testing Compilation (Make rules)...${NC}"
make re > /dev/null 2>&1
if [ -f "./push_swap" ]; then
    echo -e "${GREEN}[OK] Binary ./push_swap compiled successfully.${NC}"
else
    echo -e "${RED}[KO] Binary ./push_swap not found!${NC}"
    exit 1
fi

# Helper function to check errors
check_error() {
    local cmd="$1"
    local desc="$2"
    out=$($cmd 2>&1)
    if [ "$out" == "Error" ]; then
        echo -e "  ${GREEN}[PASS]${NC} $desc"
    else
        echo -e "  ${RED}[FAIL]${NC} $desc (Got: \"$out\")"
    fi
}

# 2. Error Handling Tests
echo -e "\n${YELLOW}[2/5] Testing Error Handling (Must print Error to stderr)...${NC}"
check_error "./push_swap 0 one 2 3" "Non-integer argument (0 one 2 3)"
check_error "./push_swap --simple 3 2 3" "Duplicate numbers (3 2 3)"
check_error "./push_swap 2147483648 1 2" "Number > INT_MAX"
check_error "./push_swap -2147483649 1 2" "Number < INT_MIN"

# Empty input test
out=$(./push_swap 2>&1)
if [ -z "$out" ]; then
    echo -e "  ${GREEN}[PASS]${NC} No parameters -> Silent (Nothing printed)"
else
    echo -e "  ${RED}[FAIL]${NC} No parameters printed something!"
fi

# 3. Strategy Flags & Checker Integration Tests
echo -e "\n${YELLOW}[3/5] Testing Strategy Flags & Sorting Logic...${NC}"
if [ -f "./checker_linux" ]; then
    CHECKER="./checker_linux"
elif [ -f "./checker" ]; then
    CHECKER="./checker"
else
    CHECKER=""
    echo -e "  ${YELLOW}[NOTE] Checker binary not found. Skipping OK/KO verification.${NC}"
fi

test_flag() {
    local flag="$1"
    local args="$2"
    if [ -n "$CHECKER" ]; then
        res=$(./push_swap $flag $args | $CHECKER $args)
        if [ "$res" == "OK" ]; then
            echo -e "  ${GREEN}[OK]${NC} Flag $flag sorted correctly."
        else
            echo -e "  ${RED}[KO]${NC} Flag $flag failed sorting!"
        fi
    else
        ops=$(./push_swap $flag $args | wc -l)
        echo -e "  ${GREEN}[DONE]${NC} Flag $flag executed ($ops operations)."
    fi
}

test_flag "--simple" "5 4 3 2 1"
test_flag "--medium" "4 67 3 87 23"
test_flag "--complex" "4 67 3 87 23"
test_flag "--adaptive" "4 67 3 87 23"

# 4. Benchmark Flag Test
echo -e "\n${YELLOW}[4/5] Testing Benchmark Flag (--bench)...${NC}"
bench_out=$(./push_swap --bench 4 67 3 87 23 2>&1 >/dev/null)
if echo "$bench_out" | grep -q "disorder"; then
    echo -e "  ${GREEN}[PASS]${NC} --bench outputs metrics to stderr properly."
else
    echo -e "  ${YELLOW}[SKIP/FAIL]${NC} --bench did not output expected format."
fi

# 5. Performance Benchmark Tests (100 & 500 Numbers)
echo -e "\n${YELLOW}[5/5] Testing Performance Targets (Operation Count)...${NC}"

# 100 Numbers Test
ARG100=$(shuf -i 0-999 -n 100 | tr "\n" " ")
OPS100=$(./push_swap $ARG100 | wc -l)
echo -n "  • 100 Numbers: $OPS100 operations "
if [ $OPS100 -lt 700 ]; then
    echo -e "${GREEN}(Excellent: < 700) [100%]${NC}"
elif [ $OPS100 -lt 1500 ]; then
    echo -e "${GREEN}(Good: < 1500) [PASS]${NC}"
elif [ $OPS100 -lt 2000 ]; then
    echo -e "${YELLOW}(Passed: < 2000) [MINIMUM PASS]${NC}"
else
    echo -e "${RED}(Failed: >= 2000 operations) [KO]${NC}"
fi

# 500 Numbers Test
ARG500=$(shuf -i 0-9999 -n 500 | tr "\n" " ")
OPS500=$(./push_swap $ARG500 | wc -l)
echo -n "  • 500 Numbers: $OPS500 operations "
if [ $OPS500 -lt 5500 ]; then
    echo -e "${GREEN}(Excellent: < 5500) [100%]${NC}"
elif [ $OPS500 -lt 8000 ]; then
    echo -e "${GREEN}(Good: < 8000) [PASS]${NC}"
elif [ $OPS500 -lt 12000 ]; then
    echo -e "${YELLOW}(Passed: < 12000) [MINIMUM PASS]${NC}"
else
    echo -e "${RED}(Failed: >= 12000 operations) [KO]${NC}"
fi

echo -e "\n${BLUE}====================================================${NC}"
echo -e "${BLUE}                 Testing Completed!                 ${NC}"
echo -e "${BLUE}====================================================${NC}"
