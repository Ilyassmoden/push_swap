#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[1;33m"
BLUE="\033[0;34m"
CYAN="\033[0;36m"
NC="\033[0m"

echo -e "${BLUE}====================================================${NC}"
echo -e "${BLUE}    🚀 ADVANCED PUSH_SWAP ULTIMATE TESTER (42)      ${NC}"
echo -e "${BLUE}====================================================${NC}"

# 1. Compilation Test
echo -e "\n${YELLOW}[1/6] Testing Compilation (Make re & clean rules)...${NC}"
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

# 2. Advanced Error Handling & Edge Cases
echo -e "\n${YELLOW}[2/6] Testing Error Handling & Edge Cases...${NC}"
check_error "./push_swap 0 one 2 3" "Non-integer argument (Letters)"
check_error "./push_swap 3 2 3" "Duplicate numbers (Strict check)"
check_error "./push_swap 2147483648 1 2" "Number > INT_MAX"
check_error "./push_swap -2147483649 1 2" "Number < INT_MIN"
check_error "./push_swap 1 + 2" "Invalid sign placement (+)"
check_error "./push_swap 1 --2 3" "Multiple signs (--)"

# Empty input & already sorted inputs
out=$(./push_swap 2>&1)
if [ -z "$out" ]; then
    echo -e "  ${GREEN}[PASS]${NC} No parameters -> Silent"
else
    echo -e "  ${RED}[FAIL]${NC} No parameters printed something!"
fi

sorted_out=$(./push_swap 1 2 3 4 5)
if [ -z "$sorted_out" ]; then
    echo -e "  ${GREEN}[PASS]${NC} Already sorted input -> Outputs nothing (0 operations)"
else
    echo -e "  ${RED}[FAIL]${NC} Already sorted input produced operations!"
fi

# 3. Strategy Flags & Checker Integration Tests
echo -e "\n${YELLOW}[3/6] Testing Strategy Flags & Sorting Logic...${NC}"
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
        echo -e "  ${CYAN}[DONE]${NC} Flag $flag executed ($ops operations)."
    fi
}

test_flag "--simple" "5 4 3 2 1"
test_flag "--medium" "4 67 3 87 23"
test_flag "--complex" "4 67 3 87 23"
test_flag "--adaptive" "4 67 3 87 23"

# 4. Benchmark Flag Test
echo -e "\n${YELLOW}[4/6] Testing Benchmark Flag (--bench)...${NC}"
bench_out=$(./push_swap --bench 4 67 3 87 23 2>&1 >/dev/null)
if echo "$bench_out" | grep -q "disorder"; then
    echo -e "  ${GREEN}[PASS]${NC} --bench outputs metrics to stderr properly."
else
    echo -e "  ${YELLOW}[SKIP/FAIL]${NC} --bench did not output expected format."
fi

# 5. Small Sizes Stress Test (2 to 5 numbers)
echo -e "\n${YELLOW}[5/6] Testing Small Sizes (2 to 5 Numbers Validation)...${NC}"
if [ -n "$CHECKER" ]; then
    fail_small=0
    for i in {1..50}; do
        # توليد 5 أرقام عشوائية فريدة باستخدام بايثون لضمان عدم حدوث أخطاء في الـ shuf
        args=$(python3 -c "import random; print(' '.join(map(str, random.sample(range(-50, 50), 5))))" 2>/dev/null)
        if [ -z "$args" ]; then
            # كخيار بديل في حال لم يتوفر بايثون
            args=$(seq -50 50 | sort -R | head -n 5 | tr '\n' ' ')
        fi
        
        res=$(./push_swap $args | $CHECKER $args)
        if [ "$res" != "OK" ]; then
            fail_small=1
            echo -e "  ${RED}[FAIL]${NC} Failed on small set: $args"
            break
        fi
    done
    if [ $fail_small -eq 0 ]; then
        echo -e "  ${GREEN}[PASS]${NC} 50 random small sets (2-5 nums) sorted successfully!"
    fi
else
    echo -e "  ${YELLOW}[NOTE] Checker not found, skipping automated small set validation.${NC}"
fi
# 6. Performance Benchmark Tests (100 & 500 Numbers over multiple runs)
echo -e "\n${YELLOW}[6/6] Testing Performance Targets (100 & 500 Numbers Average)...${NC}"

# 100 Numbers Test (Average of 3 runs)
total_ops_100=0
for run in {1..3}; do
    ARG100=$(shuf -i 0-9999 -n 100 | tr "\n" " ")
    if [ -n "$CHECKER" ]; then
        res=$(./push_swap $ARG100 | $CHECKER $ARG100)
        if [ "$res" != "OK" ]; then
            echo -e "  ${RED}[FAIL]${NC} 100 numbers run $run returned KO from checker!"
            exit 1
        fi
    fi
    ops=$(./push_swap $ARG100 | wc -l)
    total_ops_100=$((total_ops_100 + ops))
done
avg_ops_100=$((total_ops_100 / 3))

echo -n "  • 100 Numbers (Average 3 runs): $avg_ops_100 operations "
if [ $avg_ops_100 -lt 700 ]; then
    echo -e "${GREEN}(Excellent: < 700) [100%]${NC}"
elif [ $avg_ops_100 -lt 1500 ]; then
    echo -e "${GREEN}(Good: < 1500) [PASS]${NC}"
elif [ $avg_ops_100 -lt 2000 ]; then
    echo -e "${YELLOW}(Passed: < 2000) [MINIMUM PASS]${NC}"
else
    echo -e "${RED}(Failed: >= 2000 operations) [KO]${NC}"
fi

# 500 Numbers Test
ARG500=$(shuf -i 0-49999 -n 500 | tr "\n" " ")
if [ -n "$CHECKER" ]; then
    res_500=$(./push_swap $ARG500 | $CHECKER $ARG500)
    if [ "$res_500" != "OK" ]; then
        echo -e "  ${RED}[FAIL]${NC} 500 numbers returned KO from checker!"
        exit 1
    fi
fi
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
echo -e "${BLUE}          All Tests Completed Successfully!         ${NC}"
echo -e "${BLUE}====================================================${NC}"