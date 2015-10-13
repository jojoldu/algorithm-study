package pi;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

	public static int[] memories = new int[10000];
	public static int[] numbers;
	public static final int START_NUM = 3;
	public static final int END_NUM = 5;

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int caseCount = Integer.parseInt(br.readLine());

		for(int i=0;i<caseCount;i++){
			for(int j=0;j<memories.length;j++){
				memories[j] = -1;
			}

			String input = br.readLine();
			int inputLength = input.length();
			numbers = new int[inputLength];

			for(int j=0;j<inputLength;j++){
				numbers[j] = Character.getNumericValue(input.charAt(j));
			}

			System.out.println(setMemories(0));
		}

		br.close();
	}

	public static int setMemories(int start){
		int numbersLength = numbers.length;

		if(start == numbersLength){
			return 0;
		}

		if(memories[start] != -1){
			return memories[start]; 
		}else{
			int result = 999999999;

			for(int i=START_NUM; i<=END_NUM; i++){
				int end = start+i;

				if(end <= numbersLength){
					int minLevel = selectLevel(start, end) + setMemories(end);
					result = (result > minLevel)? minLevel : result;
				}
			}	
			memories[start] = result;
			return result;
		}
	}

	public static int selectLevel(int start, int end){
		if(isEqual(start, end)){
			return 1;
		}else if(isArithmetic(start, end) == 1){
			return 2;
		}else if(isArithmetic(start, end) > 1){
			return 5;
		}else if(isCrossover(start, end)){
			return 4;
		}else{
			return 10;
		}
	}
	
	public static boolean isEqual(int start, int end){
		for (int i = start + 1; i < end; i++ ) {
			if (numbers[start] != numbers[i]){
				return false;
			}
		}
		return true;
	}
	
	public static boolean isCrossover(int start, int end){
		for(int i=0;i<2;i++){
			int tempStart = start+2+i;
			for(int j=tempStart; j<end; j+=2){
				if (numbers[start+i] != numbers[j]){
					return false;
				}
			}
		}
		return true;
	}
	
	/*
	 * 단조증/감, 등차수열 모두 앞의 숫자와 뒤의 숫자의 차이만 다를뿐 같은 로직이므로 같은 메소드로 처리
	 */
	public static int isArithmetic(int start, int end){
		int gap = numbers[start+1] - numbers[start];
	
		for(int i=start; i<end-1; i++){
			if(numbers[i+1] - numbers[i] != gap){
				return -1;
			}
		}
		return Math.abs(gap);
	}
}
