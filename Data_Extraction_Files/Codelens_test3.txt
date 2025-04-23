import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Set;

public class Codelens_test3{

    // Constructor for the Simulator class
    public Simulator(Cache_L1D L1_Cache0,Cache_L1D L1_Cache1,Cache_L1D L1_Cache2,Cache_L1D L1_Cache3,Cache_L2 L2_cache){
        clock=0;
        caches=new Cache_L1D[4];
        caches[0]=L1_Cache0;
        caches[1]=L1_Cache1;
        caches[2]=L1_Cache2;
        caches[3]=L1_Cache3;
        this.L2_cache=L2_cache;
        cores=new Core[4];
        for(int i=0;i<4;i++){
            cores[i]=new Core(i,caches[i],L2_cache);
        }
        labelMapping=new HashMap<>();
        dataHazardsMapping=new HashMap<>();
        opcodes=new HashSet<>(Set.of("add","sub","mul","mv","addi","muli","and","or","xor","andi","ori","xori","rem","bne","beq","jal","jalr","lw","sw","la","li","bge","blt","j","jr","ecall"));
        
    }

    
    // Instruction Fetch stage of the pipeline
    public static FetcherResult IF(int pc,InstructionState in,int coreID,String[] program,InstructionState last,int[] instructionsExecuted) {
        // Check if instruction fetch is already done for this core
    	if(coreID==0) {
        	if(in.isDummy || in==null || in.IF_done_core0==true){
                return new FetcherResult(last,pc);
            }
        }else if(coreID==1) {
        	if(in.isDummy || in==null || in.IF_done_core1==true){
        		return new FetcherResult(last,pc);
            }
        }else if(coreID==2) {
        	if(in.isDummy || in==null || in.IF_done_core2==true){
        		return new FetcherResult(last,pc);
            }
        }else if(coreID==3) {
        	if(in.isDummy || in==null || in.IF_done_core3==true){
        		return new FetcherResult(last,pc);
            }
        }

        // Skip labels
    	if(program[pc].contains(":")) {
    		pc++;
    	}

        // Fetch the instruction
    	in.instruction=program[pc];
    	in.pc_val=pc;
    	pc++;
        instructionsExecuted[0]++;

        // Set last instruction if end of program is reached
    	if(pc==program.length) {
    		last=in;
    	}

        // Mark instruction fetch as done for the current core
    	if(coreID==0) {
        	in.IF_done_core0=true;
        }
        if(coreID==1) {
        	in.IF_done_core1=true;
        }
        if(coreID==2) {
        	in.IF_done_core2=true;
        }
        if(coreID==3) {
        	in.IF_done_core3=true;
        }	
        return new FetcherResult(last,pc);
    }
    
    // Maps labels to their corresponding instruction indices
    private void mapAllTheLabels(String[] program){
        for(int i=0;i<program.length;i++){
            String[] decodedInstruction = program[i].trim().split(" ");
            // Check for label and add to map
            if(!opcodes.contains(decodedInstruction[0].toUpperCase()) && decodedInstruction[0].contains(":")){
                String label=decodedInstruction[0].trim().replace(":", "");
                // Check for duplicate labels
                if(labelMapping.containsKey(label) && label!="" && !label.contains("#")) {
                	System.out.println("The label is that is already present is "+label+". yeah!!");
                	SimulatorGUI.console.append(label+"has already been used. Hence stopping the execution of program");
                	throw new IllegalArgumentException("Duplicate label found");
                }
                labelMapping.put(label,i+1);
            }
        }
    }

    // Prints the label mappings
    public void printLabels(){
    	System.out.println("Printing the labels ---------------------------:");
        for(Map.Entry<String,Integer> ele:labelMapping.entrySet()){
            System.out.println("Label:"+ele.getKey()+" Value:"+ele.getValue());
        }
        System.out.println();
    }

    // Initializes the program
    public void initializeProgram(String[] program){
        this.program_Seq=program;
    }

    // Runs the program
    public void runProgram(Memory mem,Map<String,String>stringVariableMapping,Map<String,Integer>nameVariableMapping,Map<String,Integer>latencies,boolean isPipelineForwardingEnabled){
        mapAllTheLabels(program_Seq);
        printLabels();
        System.out.println(program_Seq.length);
        System.out.println("Program execution started");

        boolean isDone=(cores[0].pc==program_Seq.length && cores[1].pc==program_Seq.length && cores[2].pc==program_Seq.length && cores[3].pc==program_Seq.length);

        // Execute instructions until all cores are done
        while(!isDone){
            for(int i=0;i<4;i++){
                if(cores[i].pc>=program_Seq.length){
                    continue;
                }
                this.cores[i].executeUtil(program_Seq, mem, labelMapping, stringVariableMapping, nameVariableMapping,latencies,dataHazardsMapping,isPipelineForwardingEnabled);
            } 
            this.clock++;
            System.out.println();
            System.out.println("The value of pc in core 0 is :"+cores[0].pc);
            System.out.println("The value of pc in core 1 is :"+cores[1].pc);
            System.out.println("The value of pc in core 2 is :"+cores[2].pc);
            System.out.println("The value of pc in core 3 is :"+cores[3].pc);
            isDone=(cores[0].pc==program_Seq.length && cores[1].pc==program_Seq.length && cores[2].pc==program_Seq.length && cores[3].pc==program_Seq.length);
            System.out.println();
        }

        // Process remaining instructions in pipelines
        boolean firstPipelineDone=false;
        boolean secondPipelineDone=false;
        boolean thirdPipelineDone=false;
        boolean fourthPipelineDone=false;
        System.out.println("------------------------------- The length of the pipline is "+cores[0].pipeLineQueue.size());
        
        while(!firstPipelineDone || !secondPipelineDone || !thirdPipelineDone || !fourthPipelineDone){
            this.clock++;

            // Execute for each core if pipeline is not empty
        	if(!firstPipelineDone) {
        		cores[0].execute(program_Seq, mem, labelMapping, stringVariableMapping, nameVariableMapping,latencies,dataHazardsMapping,isPipelineForwardingEnabled);
        	}
        	if(!secondPipelineDone) {
        		cores[1].execute(program_Seq, mem, labelMapping, stringVariableMapping, nameVariableMapping,latencies,dataHazardsMapping,isPipelineForwardingEnabled);
        	}
        	if(!thirdPipelineDone) {
        		cores[2].execute(program_Seq, mem, labelMapping, stringVariableMapping, nameVariableMapping,latencies,dataHazardsMapping,isPipelineForwardingEnabled);
        	}
        	if(!fourthPipelineDone) {
        		cores[3].execute(program_Seq, mem, labelMapping, stringVariableMapping, nameVariableMapping,latencies,dataHazardsMapping,isPipelineForwardingEnabled);
        	}

            // Check if last instruction is reached for each core
            if(!firstPipelineDone) {
            	InstructionState first_top=cores[0].pipeLineQueue.get(0);
                if(first_top==cores[0].lastInstruction) {
                	System.out.println("the last instruction in core 0 is:"+cores[0].lastInstruction.pc_val);
                	firstPipelineDone=true;
                	cores[0].pipeLineQueue.removeFirst();
                }else {
                	cores[0].pipeLineQueue.removeFirst();
                }
            }
            // ... (similar checks for other cores)
        }
    }


    // Prints the final register values for each core and the total clock cycles
    public void printResult(Map<String,Integer>latencies){
        for(int i=0;i<4;i++){
            System.out.println("Core :"+i);
            for(int j=0;j<32;j++){
                System.out.print(cores[i].registers[j]+" ");
            }
            System.out.println();
        }
        System.out.println("The number of clock cycles taken are:"+(this.clock-this.labelMapping.size()));
        SimulatorGUI.console.append("\nThe number of clock cycles taken for execution are "+(this.clock-1));
    }

// Get latency offset for "addi" instruction
        int latency_offset=latencies.getOrDefault("addi",0)-1;

        // Print stall counts for each core, adjusted for latency offset
        SimulatorGUI.console.append("\nThe number of stalls of core 0 are: "+(cores[0].totalStalls-latency_offset));
        SimulatorGUI.console.append("\nThe number of stalls of core 1 are: "+(cores[1].totalStalls-latency_offset));
        SimulatorGUI.console.append("\nThe number of stalls of core 2 are: "+(cores[2].totalStalls-latency_offset));
        SimulatorGUI.console.append("\nThe number of stalls of core 3 are: "+(cores[3].totalStalls-latency_offset));
        SimulatorGUI.console.append("\n");

        // Calculate max instructions executed across all cores
        int maxNumberofInstructions=Math.max(Math.max(cores[0].instructionsExecuted[0], cores[1].instructionsExecuted[0]),Math.max(cores[2].instructionsExecuted[0], cores[3].instructionsExecuted[0]));
        // Calculate overall IPC
        double IPC=(double)maxNumberofInstructions/this.clock;
        // Calculate IPC for each individual core
        double IPC0=(double)cores[0].instructionsExecuted[0]/this.clock;
        double IPC1=(double)cores[1].instructionsExecuted[0]/this.clock;
        double IPC2=(double)cores[2].instructionsExecuted[0]/this.clock;
        double IPC3=(double)cores[3].instructionsExecuted[0]/this.clock;

        // Print overall IPC and individual core IPCs
        SimulatorGUI.console.append("\nIPC : "+IPC+"\n");
        SimulatorGUI.console.append("IPC for all the cores: \n");
        SimulatorGUI.console.append("IPC of core 0: "+IPC0+"\n");
        SimulatorGUI.console.append("IPC of core 1: "+IPC1+"\n");
        SimulatorGUI.console.append("IPC of core 2: "+IPC2+"\n");
        SimulatorGUI.console.append("IPC of core 3: "+IPC3+"\n");
    }

    public int clock;
    public Core[] cores;
    public String[] program_Seq;
    public Map<String,Integer> labelMapping;
    public Set<String> opcodes;
    public static boolean isInstruction;
    public Map<Integer,Integer> dataHazardsMapping;
    public Cache_L1D[] caches;
    public Cache_L2 L2_cache;
    // public int[] instructionsExecuted;
}