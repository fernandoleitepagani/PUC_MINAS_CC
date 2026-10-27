








































class Node {
    int value;
    Node left, right;
    Node(int value) { this.value = value; }
}
Node insert(Node root, int value) {
    if (root == null) return new Node(value);
    if (value < root.value) root.left = insert(root.left, value);
    else if (value > root.value) root.right = insert(root.right, value);
    return root;
}
Node delete(Node root, int value) {
    if (root == null) return null;
    if (value < root.value) { root.left = delete(root.left, value); } 
    else if (value > root.value) { root.right = delete(root.right, value); } 
    else {
        if (root.left == null) return root.right;   // 0 or 1 child
        if (root.right == null) return root.left;

        Node successor = root.right;
        while (successor.left != null) successor = successor.left;
        root.value = successor.value;
        root.right = delete(root.right, successor.value);
    }
    return root;
}

boolean contains(Node root, int value) {
    if (root == null) return false;
    if (value == root.value) return true;
    if (value < root.value) { return contains(root.left, value); } 
    else { return contains(root.right, value); }
}
void inOrder(Node root) {
    if (root == null) return;
    inOrder(root.left);
    System.out.println(root.value);
    inOrder(root.right);
}
