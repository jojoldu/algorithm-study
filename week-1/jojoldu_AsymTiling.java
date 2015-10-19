package asymtiling;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

	public static final int DIVIDER = 1000000007;
	public static double[] memories = new double[101];

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int caseCount = Integer.parseInt(br.readLine());

		for(int j=3;j<memories.length;j++){
			memories[j] = -1;
		}
		memories[0] = 1;
		memories[1] = 1;
		memories[2] = 2;

		int n, result;
		
		for(int i=0; i<caseCount; i++){
			n = Integer.parseInt(br.readLine());
			result = fillTile(n) - fillTile(n/2);
			result = (result<0)? result+DIVIDER : result;
			
			if (n % 2 == 0) {
				result -= fillTile((n-2)/2);
				result = (result<0)? result+DIVIDER : result;
			}
			
			System.out.println(result);
		}
	}

	public static int fillTile(int index){
		
		double result = memories[index];

		if(result == -1){
			result = fillTile(index-1) + fillTile(index-2);
			memories[index] = result;
		}

		return (int)((result>DIVIDER)? result%DIVIDER : result);
	}
}