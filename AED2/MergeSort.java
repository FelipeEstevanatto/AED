import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.io.File;
import java.util.stream.Collectors;
import java.io.FileNotFoundException;

public class MergeSort {

    private static final int MAX_SIZE = 1000000;

    public static void main(String args[]) {
        String fileName = "dataset_non_ascending.txt";
        if (args.length != 0) {
            fileName = args[0];
        }

        try {
            int[] dataset = readDataset(fileName);

            long startTime = System.currentTimeMillis();
            mergeSort(dataset);
            long endTime = System.currentTimeMillis();

            long elapsedTime = endTime - startTime;

            System.out.println("Elapsed time: " + elapsedTime + " miliseconds");
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    // Read txt file (integers separated by new space)
    public static int[] readDataset(String filename) throws FileNotFoundException {
        File file = new File(filename);
        Scanner scanner = new Scanner(file);
        List<Integer> numbers = new ArrayList<>();
        while (scanner.hasNext()) {
            numbers.add(scanner.nextInt());
        }
        scanner.close();
        return numbers.stream().mapToInt(i -> i).toArray();
    }

    public static void mergeSort(int[] list) {
        if (list.length > 1) {
            int mid = list.length / 2;
            int[] left = Arrays.copyOfRange(list, 0, mid);
            int[] right = Arrays.copyOfRange(list, mid, list.length);

            mergeSort(left);
            mergeSort(right);

            merge(list, left, right);
        }

    }

    public static void merge(int[] mainArray, int[] leftArray, int[] rightArray) {
        int leftIndex = 0;
        int rightIndex = 0;
        int mainIndex = 0;
    
        while (leftIndex < leftArray.length && rightIndex < rightArray.length) {
            if (leftArray[leftIndex] < rightArray[rightIndex]) {
                mainArray[mainIndex] = leftArray[leftIndex];
                leftIndex++;
            } else {
                mainArray[mainIndex] = rightArray[rightIndex];
                rightIndex++;
            }
            mainIndex++;
        }
    
        while (leftIndex < leftArray.length) {
            mainArray[mainIndex] = leftArray[leftIndex];
            leftIndex++;
            mainIndex++;
        }
    
        while (rightIndex < rightArray.length) {
            mainArray[mainIndex] = rightArray[rightIndex];
            rightIndex++;
            mainIndex++;
        }
    }
}