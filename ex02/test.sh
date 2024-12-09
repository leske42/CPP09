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

make re > /dev/null 2>&1 # Run 'make re' to rebuild the project and suppress its output

# Check if the 'make re' command was successful
if [ $? -ne 0 ]; then
	echo -e "${RED}Error: 'make re' failed! Exiting...${RESET}"
	exit 1
fi

executable_name="PmergeMe" # Set the name of the executable to test (in this case "PmergeMe")
comparison_limits=(0 1 3 5 7 10 13 16 19 22 26 30 34 38 42 46 50 54 58 62 66 71 76 81 86 91 96 101 106 111 116 121 126) # Define an array of maximum allowed comparisons for different input sizes
total_input_sizes=33 # Total number of input sizes to test (in this case from 1 to 33)
combinations_per_input=100 # Number of combinations to test for each input size (in this case 100 combinations)
comparison_keyword="Number of comparisons" # Keyword to search for in the program's output to find the number of comparisons
# Set the range of numbers for generating random inputs
min_random_value=1
max_random_value=100
is_test_successful=true # Flag to track the success or failure of the current test
is_all_tests_successful=true # Flag to track the overall success or failure of all tests

echo -e "${YELLOW}Note:${RESET} Please ensure that the 'comparison_keyword' is present in the output"
echo -e "(in this case, '$comparison_keyword'), followed by the number on the same line"
echo -e "and the number is the last word in that line"
echo

echo -e "${YELLOW}Note:${RESET} When you change the 'total_input_sizes' variable, please ensure that"
echo -e "you aslo change the 'comparison_limits' array accordingly"
echo -e "(number of elements should match 'total_input_sizes')"
echo

# Loop through each input size (in this case from 1 to 33 numbers)
for ((current_input_size=1; current_input_size<=total_input_sizes; current_input_size++)); do
	echo -ne "${BLUE}Testing $((current_input_size)) numbers with $combinations_per_input different combinations:	${RESET}" # Print a message indicating which test is being run, with the current input size and number of combinations
	max_allowed_comparisons=${comparison_limits[current_input_size-1]} # Set the maximum allowed number of comparisons for the current input size
	is_test_successful=true # Reset the success flag for this test input size
	# Run the test for the specified number of combinations
	for ((combination_index=1; combination_index<=combinations_per_input; combination_index++)); do
		random_input_list=$(shuf -i ${min_random_value}-${max_random_value} -n $((current_input_size)) | tr '\n' ' ') # Generate a random input list of 'current_input_size' numbers between min_random_value and max_random_value
		program_output=$(./$executable_name $random_input_list) # Run the program with the generated input and capture the output
		# Check if the program execution was successful
		if [ $? -ne 0 ]; then
			echo -e "${RED}Error: './$executable_name $random_input_list' failed! Exiting...${RESET}"
			exit 1
		fi
		comparison_count=$(echo "$program_output" | grep "$comparison_keyword" | head -n 1 | awk '{print $NF}') # Extract the number of comparisons from the program's output
		# Check if the extracted value is a valid integer
		if ! [[ "$comparison_count" =~ ^-?[0-9]+$ ]]; then
			echo -e "\n${RED}Error: '$comparison_keyword' not found in output or '$comparison_count' is not a valid integer!. Exiting...${RESET}"
			exit 1
		fi
		# Check if the number of comparisons exceeds the allowed maximum for this input size
		if [ "$comparison_count" -gt "$max_allowed_comparisons" ]; then
			# If this is the first failure for this input size, print a failure message
			if $is_test_successful; then
				echo -e "${RED}KO${RESET}"
				is_all_tests_successful=false # Set the overall test success flag to false
			fi
			echo -e "${RED}Failed input: ${YELLOW}$random_input_list${RESET}	| ($comparison_count > $max_allowed_comparisons)${RESET}" # Print the failed input and the reason for failure (number of comparisons exceeded)
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
