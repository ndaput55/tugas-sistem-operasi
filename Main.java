
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    private static int selesai = 0;
    private static final Object gembok = new Object();

    private static void tambahSelesai() {
        synchronized (gembok) {
            selesai++;
        }
    }

    public static void main(String[] args) {
        System.out.println("Program dimulai\n");

        Thread t1 = new Thread(() -> {
            int hasil = 1;

            for (int i = 1; i <= 5; i++)
                hasil *= i;

            System.out.println("Thread 1 - Faktorial: 5! = " + hasil);
            tambahSelesai();
        });

        Thread t2 = new Thread(() -> {
            int a = 0, b = 1;
            StringBuilder hasil = new StringBuilder("Thread 2 - Fibonacci: ");

            for (int i = 0; i < 8; i++) {
                hasil.append(a).append(" ");
                int berikutnya = a + b;
                a = b;
                b = berikutnya;
            }

            System.out.println(hasil);
            tambahSelesai();
        });

        Thread t3 = new Thread(() -> {
            try (Scanner scanner = new Scanner(new File("pesan.txt"))) {
                System.out.print("Thread 3 - Isi file: ");
                while (scanner.hasNextLine())
                    System.out.println(scanner.nextLine());
            } catch (FileNotFoundException e) {
                System.out.println("Thread 3 - File tidak ditemukan.");
            }

            tambahSelesai();
        });

        t1.start();
        t2.start();
        t3.start();

        try {
            t1.join();
            t2.join();
            t3.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread terinterupsi!");
        }

        System.out.println("\nSemua thread selesai.");
        System.out.println("Jumlah thread selesai: " + selesai + " dari 3");
    }
}