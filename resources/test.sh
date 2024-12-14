#!/bin/bash

# Define color codes for output formatting
RED='\e[31m'
GREEN='\e[32m'
YELLOW='\e[33m'
BLUE='\e[34m'
CYAN='\e[96m'
MAGENTA='\e[35m'
RESET='\e[0m' # Reset color

# Welcome message with fancy formatting and a different color
echo -e "${MAGENTA}**********************************************************************************${RESET}"
echo -e "${MAGENTA}*                                                                                *${RESET}"
echo -e "${MAGENTA}*                   Welcome to the PmergeMe Performance Tests!                   *${RESET}"
echo -e "${MAGENTA}*                                                                                *${RESET}"
echo -e "${MAGENTA}**********************************************************************************${RESET}"
echo

# Enable this part if you want the tester to make (if you print the numbers with conditional compilation, you have to put the right command)
# For my project this would be 'make count'
#make re > /dev/null 2>&1 # Run 'make re' to rebuild the project and suppress its output
# Check if the 'make re' command was successful
#if [ $? -ne 0 ]; then
#	echo -e "${RED}Error: 'make re' failed! Exiting...${RESET}"
#	exit 1
#fi

limits() {
    local n=$1
    local k=1
    local res=0
    local a=3.0
    local b=4.0
    local v=()  # Array to store the results

    while (( k <= n )); do
        # Calculate log2((a/b) * k) using bc
        local ratio=$(echo "scale=10; $a / $b * $k" | bc)  # Calculate (a/b) * k
        local log2=$(echo "l($ratio) / l(2)" | bc -l)      # Calculate log2((a/b) * k)
        local ceil_log2=$(echo "($log2 + 0.9999) / 1" | bc) # Simulate ceil by adding 0.9999
        res=$((res + ceil_log2))  # Update res
        v+=($res)                 # Add result to array
        ((k++))
    done

    echo "${v[@]}"  # Return the array as a space-separated string
}

total_input_sizes=33 # Total number of input sizes to test (in this case from 1 to 33)
echo -ne "${BLUE}Enter maximum input size (default 33 if you press enter): ${RESET}"
while true; do
	read user_input
	if [[ -z "$user_input" ]]; then
		break
	elif [[ $user_input =~ ^[0-9]+$ ]]; then
		if [[ $user_input -gt 250 ]]; then
			echo -ne "${YELLOW}Please enter an integer up to 250: ${RESET}"
		else
			total_input_sizes=$user_input
			break
		fi
	else
		echo -ne "${YELLOW}Invalid input. Please enter a valid integer: ${RESET}"
	fi
done
comparison_keyword="comparisons" # Keyword to search for in the program's output to find the number of comparisons
echo -ne "${BLUE}Enter comparisons keyword (default 'comparisons' if you press enter): ${RESET}"
read user_input # Keyword to search for in the program's output to find the number of comparisons
if [[ -n "$user_input" ]]; then
    comparison_keyword=$user_input
fi
combinations_per_input=10 # Number of combinations to test for each input size (in this case 100 combinations)
echo -ne "${BLUE}Enter number of combinations to test per input size (default 10 if you press enter): ${RESET}"
while true; do
	read user_input
	if [[ -z "$user_input" ]]; then
		break
	elif [[ $user_input =~ ^[0-9]+$ ]]; then
		if [[ $user_input -gt 100 ]]; then
			echo -ne "${YELLOW}Please enter an integer up to 100: ${RESET}"
		else
			combinations_per_input=$user_input
			break
		fi
	else
		echo -ne "${YELLOW}Invalid input. Please enter a valid integer: ${RESET}"
	fi
done

echo
echo -e "${YELLOW}Note:${RESET} Please ensure that the 'comparison_keyword' is present in the output"
echo -e "(in this case, '$comparison_keyword'), followed by the number on the same line"
echo -e "and the number is the last word in that line"
echo

comparison_limits=($(limits $total_input_sizes)) # Define an array of maximum allowed comparisons for different input sizes
executable_name="PmergeMe" # Set the name of the executable to test (in this case "PmergeMe")
# Set the range of numbers for generating random inputs
min_random_value=1
max_random_value=$total_input_sizes;
is_test_successful=true # Flag to track the success or failure of the current test
is_all_tests_successful=true # Flag to track the overall success or failure of all tests

# Loop through each input size (in this case from 1 to 33 numbers)
for ((current_input_size=1; current_input_size<=total_input_sizes; current_input_size++)); do
	echo -ne "${BLUE}Testing $((current_input_size)) numbers with $combinations_per_input different combinations:	${RESET}" # Print a message indicating which test is being run, with the current input size and number of combinations
	max_allowed_comparisons=${comparison_limits[current_input_size-1]} # Set the maximum allowed number of comparisons for the current input size
	is_test_successful=true # Reset the success flag for this test input size
	# Run the test for the specified number of combinations
	for ((combination_index=1; combination_index<=combinations_per_input; combination_index++)); do
		half_input=$((current_input_size / 2))
		random_input_list=$(shuf -i ${min_random_value}-${max_random_value} -n $((current_input_size - $half_input)) |  tr "\n" " " ; shuf -i ${min_random_value}-${max_random_value} -n $(($half_input)) |  tr "\n" " ") # Generate a random input list of 'current_input_size' numbers between min_random_value and max_random_value
		program_output=$(./$executable_name $random_input_list) # Run the program with the generated input and capture the output
		# Check if the program execution was successful
		if [ $? -ne 0 ]; then
			echo -e "${RED}Error: './$executable_name $random_input_list' failed! Exiting...${RESET}"
			exit 1
		fi
		#Check if the sorting worked correctly
		before=$(echo "$program_output" | grep -oP '(?<=Before:).*' | xargs) # Extract the "before" and "after" lines
		after=$(echo "$program_output" | grep -oP '(?<=After:).*' | xargs)
		sorted_before=$(echo "$before" | tr ' ' '\n' | sort -n | tr '\n' ' ' | xargs) # Sort the "before" sequence
		if [[ "$sorted_before" != "$after" ]]; then # Compare "after" with the sorted "before"
			if $is_test_successful; then
				echo -e "${RED}KO${RESET}"
				is_all_tests_successful=false # Set the overall test success flag to false
			fi
			is_test_successful=false # Set the overall test success flag to false
			echo -e "${RED}Error: output for sequence ${YELLOW}$random_input_list${RED} is not sorted!${RESET}"
		fi
		# Extract the number of comparisons from the program's output
		comparison_count=$(echo "$program_output" | grep "$comparison_keyword" | head -n 1 | awk '{print $NF}')
		# Check if the extracted value is a valid integer
		if ! [[ "$comparison_count" =~ ^-?[0-9]+$ ]]; then
			echo -e "\n${RED}Error: '$comparison_keyword' not found in output or '$comparison_count' is not a valid integer!. Exiting...${RESET}"
			echo -e "${RED}Output:${RESET}" 
			echo -e "${YELLOW}$program_output${RESET}"
			exit 1
		fi
		# Check if the number of comparisons exceeds the allowed maximum for this input size
		if [ "$comparison_count" -gt "$max_allowed_comparisons" ]; then
			# If this is the first failure for this input size, print a failure message
			if $is_test_successful; then
				echo -e "${RED}KO${RESET}"
				is_all_tests_successful=false # Set the overall test success flag to false
			fi
			echo -e "${RED}Exceeded comparisons: ${YELLOW}$random_input_list${RESET} => ($comparison_count > $max_allowed_comparisons)${RESET}" # Print the failed input and the reason for failure (number of comparisons exceeded)
			is_test_successful=false # Set the test success flag to false for this input size
		fi
	done
	# If all combinations passed, print a success message
	if $is_test_successful; then
		echo -e "${GREEN}OK${RESET}"
	fi
done

# Print the overall test result based on the success flag
if $is_all_tests_successful; then
	echo
	echo -e "${GREEN}🎉🎉🎉 All tests passed successfully! 🎉🎉🎉${RESET}"
	echo -e "${GREEN}🌟 Great job! Everything is working as expected. 🌟${RESET}"
else
	echo
	echo -e "${RED}❌❌❌ Some tests failed! ❌❌❌${RESET}"
	echo -e "${RED}⚠️ Please review the failed tests above for more details. ⚠️${RESET}"
fi
