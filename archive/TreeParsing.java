package library;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class TreeParsing {

	//Parses the tree ex: (5(4()3())2())
	public TreeParsing() {
		Scanner s = new Scanner(System.in);
		if(s.hasNext()){
			int n = s.nextInt();
			int a = 0;
			while(s.hasNext()){
				String tree = "";
				while(s.hasNext()){
					String treePart = s.next();
					try{
						a = Integer.parseInt(treePart);
						break;
					}
					catch(Exception e){	}
					tree+=treePart;
				}
				Node root = constructTree(tree);

				if(root!=null){
					if(hasSum(n,root))
						System.out.println("yes");
					else
						System.out.println("no");
				}
				else{
					System.out.println("no");
				}
				n = a;
			}
		}
	}

	boolean hasSum(int goal, Node root){
		if(root==null)
			return false;
		if(root.left==null && root.right==null)
			return goal==root.value;
		return hasSum(goal-root.value,root.left)||hasSum(goal-root.value,root.right);
	}

	Queue<Boolean> parseTree(String tree){
		tree.replaceAll(" ", "");

		Queue<Boolean> parens= new LinkedList<Boolean>();
		for(char c : tree.toCharArray())
			if(c=='(')		
				parens.add(true);
			else if(c==')')
				parens.add(false);

		tree.replaceAll(" ", "");
		tree.trim();

		return parens;
	}

	Node constructTree(String tree){
		String[] nums = tree.split("[()]");
		Queue<Boolean>parens = parseTree(tree);

		Node root = null;
		int i = 1;
		while(i < nums.length){
			if(nums[i].equals("")){
				boolean paren  = parens.poll();
				if(paren){
					parens.poll();
					i++;
					root.setL=true;
				}
				else
					root = root.parent;
			}
			else{
				parens.poll();
				Node nn = new Node(Integer.parseInt(nums[i]),root);
				if(root!=null && root.setL)
					root.right = nn;
				else if(root!=null)
					root.left = nn;
				if(root!=null)
					root.setL = true;
				root = nn;
			}
			i++;
		}
		while(root!=null && root.parent!=null)
			root = root.parent;
		return root;
	}

	class Node{
		boolean setL;
		int value;
		Node left, right, parent;
		public Node(int n, Node parent){
			this.parent = parent;
			this.value =n;
		}
	}
}
