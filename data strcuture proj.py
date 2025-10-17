import tkinter as tk
from tkinter import ttk, messagebox
import math
from collections import deque
import time

class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.height = 1  # For AVL tree
        self.x = 0
        self.y = 0

class LinkedListNode:
    def __init__(self, value):
        self.value = value
        self.next = None
        self.x = 0
        self.y = 0

class DataStructureVisualizer:
    def __init__(self, root):
        self.root = root
        self.root.title("Data Structure & Algorithm Visualizer")
        self.root.geometry("1200x800")
        
        # Initialize data structures
        self.bst_root = None
        self.linked_list_head = None
        self.stack = []
        self.queue = deque()
        self.heap = []
        
        self.setup_gui()
        self.current_structure = "BST"  # Default structure
        
    def setup_gui(self):
        # Main frame
        main_frame = ttk.Frame(self.root)
        main_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        # Control panel
        control_frame = ttk.LabelFrame(main_frame, text="Controls", padding=10)
        control_frame.pack(fill=tk.X, pady=(0, 10))
        
        # Data structure selection
        struct_frame = ttk.Frame(control_frame)
        struct_frame.pack(fill=tk.X, pady=5)
        
        ttk.Label(struct_frame, text="Data Structure:").pack(side=tk.LEFT)
        self.struct_var = tk.StringVar(value="BST")
        structures = ["BST", "Linked List", "Stack", "Queue", "Min Heap"]
        struct_combo = ttk.Combobox(struct_frame, textvariable=self.struct_var, 
                                   values=structures, state="readonly")
        struct_combo.pack(side=tk.LEFT, padx=5)
        struct_combo.bind('<<ComboboxSelected>>', self.on_structure_change)
        
        # Input section
        input_frame = ttk.Frame(control_frame)
        input_frame.pack(fill=tk.X, pady=5)
        
        ttk.Label(input_frame, text="Value:").pack(side=tk.LEFT)
        self.value_entry = ttk.Entry(input_frame, width=10)
        self.value_entry.pack(side=tk.LEFT, padx=5)
        self.value_entry.bind('<Return>', lambda e: self.insert())
        
        # Operation buttons
        btn_frame = ttk.Frame(control_frame)
        btn_frame.pack(fill=tk.X, pady=5)
        
        ttk.Button(btn_frame, text="Insert/Add", command=self.insert).pack(side=tk.LEFT, padx=2)
        ttk.Button(btn_frame, text="Delete/Remove", command=self.delete).pack(side=tk.LEFT, padx=2)
        ttk.Button(btn_frame, text="Search/Find", command=self.search).pack(side=tk.LEFT, padx=2)
        ttk.Button(btn_frame, text="Clear All", command=self.clear_all).pack(side=tk.LEFT, padx=2)
        ttk.Button(btn_frame, text="Traverse", command=self.traverse).pack(side=tk.LEFT, padx=2)
        
        # Animation speed control
        speed_frame = ttk.Frame(control_frame)
        speed_frame.pack(fill=tk.X, pady=5)
        
        ttk.Label(speed_frame, text="Animation Speed:").pack(side=tk.LEFT)
        self.speed_var = tk.DoubleVar(value=1.0)
        speed_scale = ttk.Scale(speed_frame, from_=0.1, to=2.0, variable=self.speed_var, 
                               orient=tk.HORIZONTAL)
        speed_scale.pack(side=tk.LEFT, padx=5, fill=tk.X, expand=True)
        
        # Canvas for visualization
        self.canvas = tk.Canvas(main_frame, bg='white', relief=tk.SUNKEN, borderwidth=2)
        self.canvas.pack(fill=tk.BOTH, expand=True)
        
        # Status bar
        self.status_var = tk.StringVar(value="Ready - Select a data structure and start visualizing!")
        status_bar = ttk.Label(main_frame, textvariable=self.status_var, relief=tk.SUNKEN)
        status_bar.pack(fill=tk.X, pady=(10, 0))
        
    def on_structure_change(self, event=None):
        self.current_structure = self.struct_var.get()
        self.clear_canvas()
        self.update_status(f"Switched to {self.current_structure}")
        self.draw_structure()
    
    def get_animation_delay(self):
        return (2.0 - self.speed_var.get()) * 500  # Convert to milliseconds
    
    def clear_canvas(self):
        self.canvas.delete("all")
    
    def update_status(self, message):
        self.status_var.set(message)
        self.root.update()
    
    def validate_input(self):
        try:
            value = self.value_entry.get()
            if not value:
                return None
            return int(value)
        except ValueError:
            messagebox.showerror("Invalid Input", "Please enter a valid integer")
            return None
    
    # BST Operations
    def bst_insert(self, root, value):
        if not root:
            return TreeNode(value)
        
        if value < root.value:
            root.left = self.bst_insert(root.left, value)
        else:
            root.right = self.bst_insert(root.right, value)
        
        return root
    
    def bst_delete(self, root, value):
        if not root:
            return root
        
        if value < root.value:
            root.left = self.bst_delete(root.left, value)
        elif value > root.value:
            root.right = self.bst_delete(root.right, value)
        else:
            if not root.left:
                return root.right
            elif not root.right:
                return root.left
            
            temp = self.bst_min_value(root.right)
            root.value = temp.value
            root.right = self.bst_delete(root.right, temp.value)
        
        return root
    
    def bst_min_value(self, root):
        current = root
        while current.left:
            current = current.left
        return current
    
    def bst_search(self, root, value):
        if not root or root.value == value:
            return root
        
        if value < root.value:
            return self.bst_search(root.left, value)
        return self.bst_search(root.right, value)
    
    # Linked List Operations
    def ll_insert(self, value):
        new_node = LinkedListNode(value)
        if not self.linked_list_head:
            self.linked_list_head = new_node
        else:
            current = self.linked_list_head
            while current.next:
                current = current.next
            current.next = new_node
    
    def ll_delete(self, value):
        if not self.linked_list_head:
            return
        
        if self.linked_list_head.value == value:
            self.linked_list_head = self.linked_list_head.next
            return
        
        current = self.linked_list_head
        while current.next and current.next.value != value:
            current = current.next
        
        if current.next:
            current.next = current.next.next
    
    def ll_search(self, value):
        current = self.linked_list_head
        position = 0
        while current:
            if current.value == value:
                return position
            current = current.next
            position += 1
        return -1
    
    # Stack Operations
    def stack_push(self, value):
        self.stack.append(value)
    
    def stack_pop(self):
        if self.stack:
            return self.stack.pop()
        return None
    
    # Queue Operations
    def queue_enqueue(self, value):
        self.queue.append(value)
    
    def queue_dequeue(self):
        if self.queue:
            return self.queue.popleft()
        return None
    
    # Heap Operations
    def heap_insert(self, value):
        self.heap.append(value)
        self.heapify_up(len(self.heap) - 1)
    
    def heapify_up(self, index):
        parent = (index - 1) // 2
        if index > 0 and self.heap[index] < self.heap[parent]:
            self.heap[index], self.heap[parent] = self.heap[parent], self.heap[index]
            self.heapify_up(parent)
    
    def heap_extract_min(self):
        if not self.heap:
            return None
        if len(self.heap) == 1:
            return self.heap.pop()
        
        root = self.heap[0]
        self.heap[0] = self.heap.pop()
        self.heapify_down(0)
        return root
    
    def heapify_down(self, index):
        smallest = index
        left = 2 * index + 1
        right = 2 * index + 2
        
        if left < len(self.heap) and self.heap[left] < self.heap[smallest]:
            smallest = left
        if right < len(self.heap) and self.heap[right] < self.heap[smallest]:
            smallest = right
        
        if smallest != index:
            self.heap[index], self.heap[smallest] = self.heap[smallest], self.heap[index]
            self.heapify_down(smallest)
    
    # Main Operations
    def insert(self):
        value = self.validate_input()
        if value is None:
            return
        
        if self.current_structure == "BST":
            self.bst_root = self.bst_insert(self.bst_root, value)
            self.update_status(f"Inserted {value} into BST")
        elif self.current_structure == "Linked List":
            self.ll_insert(value)
            self.update_status(f"Inserted {value} into Linked List")
        elif self.current_structure == "Stack":
            self.stack_push(value)
            self.update_status(f"Pushed {value} onto Stack")
        elif self.current_structure == "Queue":
            self.queue_enqueue(value)
            self.update_status(f"Enqueued {value} into Queue")
        elif self.current_structure == "Min Heap":
            self.heap_insert(value)
            self.update_status(f"Inserted {value} into Min Heap")
        
        self.value_entry.delete(0, tk.END)
        self.draw_structure()
    
    def delete(self):
        value = self.validate_input()
        if value is None:
            return
        
        if self.current_structure == "BST":
            self.bst_root = self.bst_delete(self.bst_root, value)
            self.update_status(f"Deleted {value} from BST")
        elif self.current_structure == "Linked List":
            self.ll_delete(value)
            self.update_status(f"Deleted {value} from Linked List")
        elif self.current_structure == "Stack":
            popped = self.stack_pop()
            self.update_status(f"Popped {popped} from Stack" if popped else "Stack is empty")
        elif self.current_structure == "Queue":
            dequeued = self.queue_dequeue()
            self.update_status(f"Dequeued {dequeued} from Queue" if dequeued else "Queue is empty")
        elif self.current_structure == "Min Heap":
            extracted = self.heap_extract_min()
            self.update_status(f"Extracted min: {extracted} from Heap" if extracted else "Heap is empty")
        
        self.value_entry.delete(0, tk.END)
        self.draw_structure()
    
    def search(self):
        value = self.validate_input()
        if value is None:
            return
        
        if self.current_structure == "BST":
            result = self.bst_search(self.bst_root, value)
            self.update_status(f"Found {value} in BST" if result else f"{value} not found in BST")
        elif self.current_structure == "Linked List":
            position = self.ll_search(value)
            self.update_status(f"Found {value} at position {position}" if position != -1 else f"{value} not found in Linked List")
        else:
            self.update_status("Search not implemented for this structure")
        
        self.highlight_value(value)
    
    def traverse(self):
        if self.current_structure == "BST":
            self.bst_traverse_animation(self.bst_root)
        else:
            self.update_status("Traversal animation available only for BST")
    
    def clear_all(self):
        if self.current_structure == "BST":
            self.bst_root = None
        elif self.current_structure == "Linked List":
            self.linked_list_head = None
        elif self.current_structure == "Stack":
            self.stack = []
        elif self.current_structure == "Queue":
            self.queue.clear()
        elif self.current_structure == "Min Heap":
            self.heap = []
        
        self.update_status("Cleared all data")
        self.draw_structure()
    
    # Drawing Methods
    def draw_structure(self):
        self.clear_canvas()
        
        if self.current_structure == "BST":
            self.draw_bst()
        elif self.current_structure == "Linked List":
            self.draw_linked_list()
        elif self.current_structure == "Stack":
            self.draw_stack()
        elif self.current_structure == "Queue":
            self.draw_queue()
        elif self.current_structure == "Min Heap":
            self.draw_heap()
    
    def draw_bst(self):
        if not self.bst_root:
            self.canvas.create_text(600, 200, text="BST is empty", font=("Arial", 16), fill="gray")
            return
        
        # Calculate positions
        self.calculate_bst_positions(self.bst_root, 600, 100, 300)
        
        # Draw nodes and edges
        self.draw_bst_edges(self.bst_root)
        self.draw_bst_nodes(self.bst_root)
    
    def calculate_bst_positions(self, node, x, y, horizontal_spacing):
        if node:
            node.x = x
            node.y = y
            
            if node.left:
                self.calculate_bst_positions(node.left, x - horizontal_spacing, y + 80, horizontal_spacing // 1.8)
            if node.right:
                self.calculate_bst_positions(node.right, x + horizontal_spacing, y + 80, horizontal_spacing // 1.8)
    
    def draw_bst_edges(self, node):
        if node:
            if node.left:
                self.canvas.create_line(node.x, node.y, node.left.x, node.left.y, arrow=tk.LAST, width=2)
                self.draw_bst_edges(node.left)
            if node.right:
                self.canvas.create_line(node.x, node.y, node.right.x, node.right.y, arrow=tk.LAST, width=2)
                self.draw_bst_edges(node.right)
    
    def draw_bst_nodes(self, node):
        if node:
            # Draw node
            self.canvas.create_oval(node.x-25, node.y-25, node.x+25, node.y+25, 
                                   fill='lightblue', outline='darkblue', width=2)
            self.canvas.create_text(node.x, node.y, text=str(node.value), 
                                   font=("Arial", 12, "bold"), fill='black')
            
            # Draw children recursively
            self.draw_bst_nodes(node.left)
            self.draw_bst_nodes(node.right)
    
    def draw_linked_list(self):
        if not self.linked_list_head:
            self.canvas.create_text(600, 200, text="Linked List is empty", font=("Arial", 16), fill="gray")
            return
        
        current = self.linked_list_head
        x, y = 200, 200
        node_spacing = 120
        
        while current:
            current.x = x
            current.y = y
            
            # Draw node
            self.canvas.create_rectangle(x-30, y-20, x+30, y+20, fill='lightgreen', outline='darkgreen', width=2)
            self.canvas.create_text(x, y, text=str(current.value), font=("Arial", 12, "bold"))
            
            # Draw pointer if there's a next node
            if current.next:
                self.canvas.create_line(x+30, y, x+90, y, arrow=tk.LAST, width=2)
                self.canvas.create_text(x+60, y-15, text="next", font=("Arial", 8))
            
            x += node_spacing
            current = current.next
        
        # Draw head pointer
        self.canvas.create_text(150, 200, text="head", font=("Arial", 10, "bold"))
        self.canvas.create_line(170, 200, 170, 200, arrow=tk.LAST, width=2)
    
    def draw_stack(self):
        x, y_base = 600, 500
        width, height = 80, 40
        
        # Draw stack container
        self.canvas.create_rectangle(x-60, 100, x+60, 500, outline='black', width=2)
        self.canvas.create_text(x, 80, text="STACK", font=("Arial", 14, "bold"))
        self.canvas.create_text(x, 520, text="top →", font=("Arial", 10))
        
        if not self.stack:
            self.canvas.create_text(x, 300, text="Empty", font=("Arial", 12), fill="gray")
            return
        
        # Draw stack elements
        for i, value in enumerate(reversed(self.stack)):
            y = y_base - (i * height)
            self.canvas.create_rectangle(x-width, y-height, x+width, y, 
                                       fill='orange', outline='darkorange', width=2)
            self.canvas.create_text(x, y-height//2, text=str(value), font=("Arial", 12, "bold"))
    
    def draw_queue(self):
        x_start, y = 200, 300
        width, height = 80, 60
        
        # Draw queue container
        self.canvas.create_line(x_start, y, x_start+600, y, width=3)
        self.canvas.create_line(x_start, y+height, x_start+600, y+height, width=3)
        self.canvas.create_text(x_start-50, y+30, text="front →", font=("Arial", 10))
        self.canvas.create_text(x_start+650, y+30, text="← rear", font=("Arial", 10))
        
        if not self.queue:
            self.canvas.create_text(500, 350, text="Empty Queue", font=("Arial", 12), fill="gray")
            return
        
        # Draw queue elements
        for i, value in enumerate(self.queue):
            x = x_start + (i * (width + 10))
            self.canvas.create_rectangle(x, y, x+width, y+height, 
                                       fill='lightcoral', outline='darkred', width=2)
            self.canvas.create_text(x+width//2, y+height//2, text=str(value), font=("Arial", 12, "bold"))
    
    def draw_heap(self):
        if not self.heap:
            self.canvas.create_text(600, 200, text="Heap is empty", font=("Arial", 16), fill="gray")
            return
        
        # Draw heap as a complete binary tree
        n = len(self.heap)
        levels = math.floor(math.log2(n)) + 1
        
        # Calculate positions
        positions = []
        for i in range(n):
            level = math.floor(math.log2(i+1))
            nodes_in_level = 2 ** level
            position_in_level = i + 1 - 2 ** level
            
            x_spacing = 800 // (nodes_in_level + 1)
            x = x_spacing * (position_in_level + 1)
            y = 100 + level * 100
            
            positions.append((x, y))
        
        # Draw edges
        for i in range(n):
            left_child = 2 * i + 1
            right_child = 2 * i + 2
            
            if left_child < n:
                self.canvas.create_line(positions[i][0], positions[i][1], 
                                      positions[left_child][0], positions[left_child][1], 
                                      width=2)
            if right_child < n:
                self.canvas.create_line(positions[i][0], positions[i][1], 
                                      positions[right_child][0], positions[right_child][1], 
                                      width=2)
        
        # Draw nodes
        for i, (x, y) in enumerate(positions):
            self.canvas.create_oval(x-20, y-20, x+20, y+20, 
                                  fill='lightyellow', outline='goldenrod', width=2)
            self.canvas.create_text(x, y, text=str(self.heap[i]), font=("Arial", 10, "bold"))
    
    def highlight_value(self, value):
        self.draw_structure()  # Redraw to clear previous highlights
        
        if self.current_structure == "BST":
            node = self.bst_search(self.bst_root, value)
            if node:
                self.canvas.create_oval(node.x-30, node.y-30, node.x+30, node.y+30, 
                                      outline='red', width=3)
        elif self.current_structure == "Linked List":
            current = self.linked_list_head
            while current:
                if current.value == value:
                    self.canvas.create_rectangle(current.x-35, current.y-25, 
                                               current.x+35, current.y+25,
                                               outline='red', width=3)
                    break
                current = current.next
    
    def bst_traverse_animation(self, node):
        if node:
            # Pre-order traversal with animation
            self.highlight_value(node.value)
            self.root.update()
            self.root.after(self.get_animation_delay())
            
            self.bst_traverse_animation(node.left)
            self.bst_traverse_animation(node.right)

def main():
    root = tk.Tk()
    app = DataStructureVisualizer(root)
    root.mainloop()

if __name__ == "__main__":
    main()