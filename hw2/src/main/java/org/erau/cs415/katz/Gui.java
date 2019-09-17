package org.erau.cs415.katz;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class Gui extends JFrame {
    private JTextField answerField;
    private JButton one, two, three, four, five, six, seven, eight, nine, zero, add, sub, mul, div, eq;
    private String sTemp1;
    private String sTemp2;
    private double answer = 0.0;
    private boolean equalsCliced = false, opChosen = false;
    private char operation = ' ';

    public Gui() {
        super("Ferrin's Calculator");

        Font sansSerif24 = new Font("SansSerif", Font.PLAIN, 24);
        Font sansSerif48 = new Font("SansSerif", Font.PLAIN, 48);

        answerField = new JTextField(null, 20);
        answerField.setEditable(false);
        answerField.setFont(sansSerif24);

        one = new JButton("1"); one.setFont(sansSerif48);
        two = new JButton("2"); two.setFont(sansSerif48);
        three = new JButton("3"); three.setFont(sansSerif48);
        four = new JButton("4"); four.setFont(sansSerif48);
        five = new JButton("5"); five.setFont(sansSerif48);
        six = new JButton("6"); six.setFont(sansSerif48);
        seven = new JButton("7"); seven.setFont(sansSerif48);
        eight = new JButton("8"); eight.setFont(sansSerif48);
        nine = new JButton("9"); nine.setFont(sansSerif48);
        zero = new JButton("0"); zero.setFont(sansSerif48);
        add = new JButton("+"); add.setFont(sansSerif48);
        sub = new JButton("-"); sub.setFont(sansSerif48);
        mul = new JButton("*"); mul.setFont(sansSerif48);
        div = new JButton("/"); div.setFont(sansSerif48);
        eq = new JButton("="); eq.setFont(sansSerif48);

        Dimension dimension = new Dimension(150, 75);

        one.setPreferredSize(dimension);
        two.setPreferredSize(dimension);
        three.setPreferredSize(dimension);
        four.setPreferredSize(dimension);
        five.setPreferredSize(dimension);
        six.setPreferredSize(dimension);
        seven.setPreferredSize(dimension);
        eight.setPreferredSize(dimension);
        nine.setPreferredSize(dimension);
        zero.setPreferredSize(new Dimension(460, 75));
        add.setPreferredSize(new Dimension(227, 75));
        sub.setPreferredSize(new Dimension(227, 75));
        mul.setPreferredSize(new Dimension(227, 75));
        div.setPreferredSize(new Dimension(227, 75));
        eq.setPreferredSize(new Dimension(460, 75));

        Numbers n = new Numbers();
        Calc c = new Calc();

        one.addActionListener(n);
        two.addActionListener(n);
        three.addActionListener(n);
        four.addActionListener(n);
        five.addActionListener(n);
        six.addActionListener(n);
        seven.addActionListener(n);
        eight.addActionListener(n);
        nine.addActionListener(n);
        zero.addActionListener(n);

        add.addActionListener(c);
        sub.addActionListener(c);
        mul.addActionListener(c);
        div.addActionListener(c);
        eq.addActionListener(c);


        JPanel contentPanel = new JPanel();
        contentPanel.setBackground(Color.lightGray);
        contentPanel.setLayout(new FlowLayout());

        contentPanel.add(answerField, BorderLayout.NORTH);
        contentPanel.add(one);
        contentPanel.add(two);
        contentPanel.add(three);
        contentPanel.add(four);
        contentPanel.add(five);
        contentPanel.add(six);
        contentPanel.add(seven);
        contentPanel.add(eight);
        contentPanel.add(nine);
        contentPanel.add(zero);
        contentPanel.add(add);
        contentPanel.add(sub);
        contentPanel.add(mul);
        contentPanel.add(div);
        contentPanel.add(eq);

        this.setContentPane(contentPanel);
    }

    private class Numbers implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            JButton src = (JButton) e.getSource();

            if (src.equals(one)) {
                if (!opChosen) {
                    if (sTemp1 == null) {
                        sTemp1 = "1";
                    } else {
                        sTemp1 += "1";
                    }
                } else {
                    if (sTemp2 == null) {
                        sTemp2 = "1";
                    } else {
                        sTemp2 += "1";
                    }
                }
            } else if (src.equals(two)) {
                if (!opChosen) {
                    if (sTemp1 == null) {
                        sTemp1 = "2";
                    } else {
                        sTemp1 += "2";
                    }
                } else {
                    if (sTemp2 == null) {
                        sTemp2 = "2";
                    } else {
                        sTemp2 += "2";
                    }
                }
            } else if (src.equals(three)) {
                if (!opChosen) {
                    if (sTemp1 == null) {
                        sTemp1 = "3";
                    } else {
                        sTemp1 += "3";
                    }
                } else {
                    if (sTemp2 == null) {
                        sTemp2 = "3";
                    } else {
                        sTemp2 += "3";
                    }
                }
            } else if (src.equals(four)) {
                if (!opChosen) {
                    if (sTemp1 == null) {
                        sTemp1 = "4";
                    } else {
                        sTemp1 += "4";
                    }
                } else {
                    if (sTemp2 == null) {
                        sTemp2 = "4";
                    } else {
                        sTemp2 += "4";
                    }
                }
            } else if (src.equals(five)) {
                if (!opChosen) {
                    if (sTemp1 == null) {
                        sTemp1 = "5";
                    } else {
                        sTemp1 += "5";
                    }
                } else {
                    if (sTemp2 == null) {
                        sTemp2 = "5";
                    } else {
                        sTemp2 += "5";
                    }
                }
            } else if (src.equals(six)) {
                if (!opChosen) {
                    if (sTemp1 == null) {
                        sTemp1 = "6";
                    } else {
                        sTemp1 += "6";
                    }
                } else {
                    if (sTemp2 == null) {
                        sTemp2 = "6";
                    } else {
                        sTemp2 += "6";
                    }
                }
            } else if (src.equals(seven)) {
                if (!opChosen) {
                    if (sTemp1 == null) {
                        sTemp1 = "7";
                    } else {
                        sTemp1 += "7";
                    }
                } else {
                    if (sTemp2 == null) {
                        sTemp2 = "7";
                    } else {
                        sTemp2 += "7";
                    }
                }
            } else if (src.equals(eight)) {
                if (!opChosen) {
                    if (sTemp1 == null) {
                        sTemp1 = "8";
                    } else {
                        sTemp1 += "8";
                    }
                } else {
                    if (sTemp2 == null) {
                        sTemp2 = "8";
                    } else {
                        sTemp2 += "8";
                    }
                }
            } else if (src.equals(nine)) {
                if (!opChosen) {
                    if (sTemp1 == null) {
                        sTemp1 = "9";
                    } else {
                        sTemp1 += "9";
                    }
                } else {
                    if (sTemp2 == null) {
                        sTemp2 = "9";
                    } else {
                        sTemp2 += "9";
                    }
                }
            } else if (src.equals(zero)) {
                if (!opChosen) {
                    if (sTemp1 == null) {
                        sTemp1 = "0";
                    } else {
                        sTemp1 += "0";
                    }
                } else {
                    if (sTemp2 == null) {
                        sTemp2 = "0";
                    } else {
                        sTemp2 += "0";
                    }
                }
            }

            if (!equalsCliced)
                if (!opChosen) {
                    answerField.setText(sTemp1);
                } else {
                    answerField.setText(sTemp2);
                }
        }
    }

    private class Calc implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            JButton src = (JButton) e.getSource();

            if (src.equals(add)) {
                if (sTemp1 == null) {
                    System.out.println("Choose your numbers first!");
                } else if (sTemp2 == null) {
                    opChosen = true;
                    operation = '+';
                } else {
                    System.out.println("Two inputs only");
                }
            } else if (src.equals(sub)) {
                if (sTemp1 == null) {
                    System.out.println("Choose your numbers first!");
                } else if (sTemp2 == null) {
                    opChosen = true;
                    operation = '-';
                } else {
                    System.out.println("Two inputs only");
                }
            } else if (src.equals(mul)) {
                if (sTemp1 == null) {
                    System.out.println("Choose your numbers first!");
                } else if (sTemp2 == null) {
                    opChosen = true;
                    operation = '*';
                } else {
                    System.out.println("Two inputs only");
                }
            } else if (src.equals(div)) {
                if (sTemp1 == null) {
                    System.out.println("Choose your numbers first!");
                } else if (sTemp2 == null) {
                    opChosen = true;
                    operation = '/';
                } else {
                    System.out.println("Two inputs only");
                }
            } else if (src.equals(eq)) {
                String sAnswer;
                if (sTemp1 == null) {
                    System.out.println("Choose your numbers first!");
                } else if (sTemp2 == null) {
                    answer = Double.parseDouble(sTemp1);
                    sAnswer = Double.toString(answer);
                    answerField.setText(sAnswer);
                } else {
                    double d1 = Double.parseDouble(sTemp1);
                    double d2 = Double.parseDouble(sTemp2);

                    switch (operation){
                        case '+':
                            answer = d1 + d2;
                            break;
                        case '-':
                            answer = d1 - d2;
                            break;
                        case '*':
                            answer = d1 * d2;
                            break;
                        case '/':
                            answer = d1 / d2;
                            break;
                    }

                    sAnswer = Double.toString(answer);
                    answerField.setText(sAnswer);
                }
            }
        }
    }
}
