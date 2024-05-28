import java.util.ArrayList;
import java.util.List;

public class FCFS {
    static int[] p = {1,2,3,4};
    static int[] at = {0,1,2,4};
    static int[] bt = {5,3,3,1};
    static int[] ft = new int[4];
    static int[] tt = new int[4];
    static int[] wt = new int[4];
    void fcfs(){
        List<Integer> list = new ArrayList<>();
        int time = 0;
        int totaltime = 0;
        for(int i=0;i<4;i++){
            ft[i] = totaltime + bt[i];
            totaltime += bt[i];
        }
        for(int i=0;i<4;i++){
            tt[i] = ft[i] - at[i];
        }
        for(int i=0;i<4;i++){
            wt[i] = tt[i] - bt[i];
        }
    }

    void display(){
        System.out.println("Process    ArrivalTime    BurstTime   FinishTime    TotalTime   WaitingTime");
        for(int i=0;i<4;i++){
            System.out.println(p[i]+"             "+at[i]+"               "+bt[i]+"            "+ft[i]+"         "+tt[i]+"          "+wt[i]);
        }
    }

    public static void main(String[] args) {
        FCFS np = new FCFS();
        np.fcfs();
        np.display();
    }
}
