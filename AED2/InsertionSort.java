import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.io.File;
import java.util.stream.Collectors;


public class InsertionSort {

    private static final int MAX_SIZE = 1000000;

    public static void main(String args[]) {
        // Get dataset
        String fileName = "dataset_95_sorted.txt";
        if (args.length != 0) {
            fileName = args[0];
        }

        int[] dataset = readDataset(fileName);

        long startTime = System.nanoTime();
        int[] newList = insertionSort(dataset);
        long endTime = System.nanoTime();

        long elapsedTime = endTime - startTime;

        System.out.println("Elapsed time: " + elapsedTime/1000000 + " miliseconds");
    }

    public static int[] readDataset(String filename) {
        int[] records = new int[MAX_SIZE];
        File file = new File(filename);
        try {
            Scanner scanner = new Scanner(file);
            int i = 0;
            while (scanner.hasNextLine()) {
                records[i] = Integer.parseInt(scanner.nextLine());
                i++;
            }
            scanner.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return records;
    }

    public static int[] insertionSort(int[] list) {
        for (int i = 1; i < list.length; i++) {
            int key = list[i];
            int j = i - 1;
            while (j >= 0 && list[j] > key) {
                list[j + 1] = list[j];
                j = j - 1;
            }
            list[j + 1] = key;
        }

        return list;
    }
}