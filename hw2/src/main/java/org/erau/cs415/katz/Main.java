package org.erau.cs415.katz;

import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        Gui gui = new Gui();
        gui.setSize(500,800);
        gui.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        gui.setVisible(true);
        gui.setResizable(false);
    }
}
