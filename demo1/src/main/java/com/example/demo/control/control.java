package com.example.demo.control;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/wordladder")
public class control {

    @RequestMapping("/hello")
    public static String main(HttpServletRequest request) {
        String startword = request.getParameter("start");
        String endword = request.getParameter("end");
        Set<String> wordList = null;  
	    File file = new File("E:/ren-rui/dictionary.txt");
	    try {     
	        InputStreamReader read = new InputStreamReader(new FileInputStream(file), "utf-8");  
	        if (file.isFile() && file.exists()) {  
	             wordList = new HashSet<String>();  
	             BufferedReader br = new BufferedReader(read);  
	             String txt = null;  
	             while ((txt = br.readLine()) != null) {  
	             wordList.add(txt);  
	             }  
	        br.close();    
	      }  
	        read.close();  
	    } 
	    catch (Exception e) {  
	        e.printStackTrace();  
	    }
	    if(wordList.contains(startword)&&wordList.contains(endword)&&startword.length()==endword.length()) {	    
        control WL = new control();
        List<List<String>> ladders = WL.findLadders(startword,endword,wordList);
        for(List<String> list : ladders){
            System.out.println(list);
            String lad = "";
            for(int i = 0;i < list.size();i++) {
            	lad = lad.concat(list.get(i)+" ");
            }
            return lad;
        }
    } 
	    else {
	    	return "No ladder between "+startword+" and "+endword+" .";
	    	}
		return "";
}
    
    public List<List<String>> findLadders(String startWord, String endWord, Set<String> Dict){
        List<List<String>> Ladders = new ArrayList<List<String>>();
        HashMap<String, List<String>> preGraph = new HashMap<String, List<String>>();
        HashMap<String, Integer> distance = new HashMap<String, Integer>();       
        Dict.add(startWord);
        Dict.add(endWord);
        for(String word : Dict){
            preGraph.put(word, new ArrayList<String>());
        }
        bfs(preGraph, distance, startWord, Dict);
        dfs(Ladders, new ArrayList<String>(), endWord, startWord, distance, preGraph);
        return Ladders;
    }
    public List<String> getNextWords(String words, Set<String> wordDict){
        List<String> nextWords = new ArrayList<String>();
        for(int i = 0; i < words.length(); i++){
            for(char c = 'a'; c <= 'z'; c++){
                if(c == words.charAt(i)) continue; 
                char[] arr = words.toCharArray();
                arr[i] = c;
                String next = new String(arr);
                if(wordDict.contains(next)) nextWords.add(next);
            }
        }
        return nextWords;
    }    
    public void bfs(HashMap<String, List<String>> preGraph, HashMap<String, Integer> distance, String beginWord, Set<String> wordDict){
        LinkedList<String> queue = new LinkedList<String>();
        queue.offer(beginWord);
        distance.put(beginWord, 0);       
        while(!queue.isEmpty()){
            String curr = queue.poll();
            for(String next : getNextWords(curr, wordDict)){
                preGraph.get(next).add(curr);
                if(!distance.containsKey(next)){
                    distance.put(next, distance.get(curr) + 1);
                    queue.offer(next);
                }
            }
        }
    }
    public void dfs(List<List<String>> Ladders, List<String> path, String curr, String startWord, HashMap<String, Integer> distance, HashMap<String, List<String>> preGraph){
        if(curr.equals(startWord)){
            path.add(curr);
            Collections.reverse(path);
            Ladders.add(path);
            return;
        }        
        for(String next : preGraph.get(curr)){
            if(distance.get(curr) - 1 == distance.get(next)){
                path.add(curr);
                dfs(Ladders, new ArrayList<String>(path), next, startWord, distance, preGraph);
                path.remove(path.size() - 1);
            }
        }
    }  
}
