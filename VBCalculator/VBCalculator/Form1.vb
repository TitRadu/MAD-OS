Public Class Calculator
    Dim celsius, fahrenheit, kelvin As Double
    Dim firstNumber As Double
    Dim secondNumber As Double
    Dim result As Double
    Dim operationA As String
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        textBoxSt.Text = "0"
        Me.Width = 250
        Me.Height = 421
        textBoxSt.Width = 215
        Me.Text = "Standard Calculator"

        cmbUC.Text = "Choose one:"
        cmbUC.Items.Add("Kilometers to Miles")
        cmbUC.Items.Add("Miles to Kilometers")
        cmbUC.Items.Add("Kilograms to LBS")
        cmbUC.Items.Add("LBS to Kilograms")

    End Sub
    Private Sub StandardToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles StandardToolStripMenuItem.Click
        Me.Width = 250
        textBoxSt.Width = 215
        Me.Text = "Standard Calculator"

    End Sub

    Private Sub ScientificToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ScientificToolStripMenuItem.Click
        Me.Width = 505
        textBoxSt.Width = 460
        Me.Text = "Scientific Calculator"
    End Sub

    Private Sub TemperatureToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles TemperatureToolStripMenuItem.Click
        Me.Width = 835
        textBoxSt.Width = 460
        Me.Text = "Temperature Conversion"
        GroupBox1.Visible = True
        GroupBox3.Visible = False
        GroupBox4.Visible = False

    End Sub

    Private Sub MultiplicationToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles MultiplicationToolStripMenuItem.Click
        Me.Width = 861
        textBoxSt.Width = 460
        Me.Text = "Multiplication Times Table"
        GroupBox3.Location = New Point(496, 32)
        GroupBox3.Visible = True
        GroupBox1.Visible = False
        GroupBox4.Visible = False


    End Sub

    Private Sub btnConvert_Click(sender As Object, e As EventArgs) Handles btnConvert.Click
        If textBoxT.Text = "" Or textBoxT.Text = "." Then
            MessageBox.Show("Introduce a value to convert!", "Value Required", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Return

        End If

        If chkCF.Checked = True And chkFC.Checked = False And chkCK.Checked = False And chkCK.Checked = False Then
            'Celsius==>>Fahrenheit
            celsius = Double.Parse(textBoxT.Text)
            lblT.Text = ((((9 * celsius) / 5) + 32).ToString)
            Return
        End If

        If chkCF.Checked = False And chkFC.Checked = True And chkCK.Checked = False And chkCK.Checked = False Then
            'Fahrenheit==>>Celsius                
            fahrenheit = Double.Parse(textBoxT.Text)
            lblT.Text = ((((fahrenheit - 32) * 5) / 9).ToString)
            Return
        End If

        If chkCF.Checked = False And chkFC.Checked = False And chkCK.Checked = True And chkKC.Checked = False Then
            'Celsius==>Kelvin
            celsius = Double.Parse(textBoxT.Text)
            lblT.Text = celsius + 273.15
            Return
        End If

        If chkCF.Checked = False And chkFC.Checked = False And chkCK.Checked = False And chkKC.Checked = True Then
            'Kelvin==>Celsius
            kelvin = Double.Parse(textBoxT.Text)
            lblT.Text = kelvin - 273.15
            Return
        Else
            MessageBox.Show("Check a convert method(only one)!", "Check Required", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Return
        End If



    End Sub

    Private Sub btnReset_Click(sender As Object, e As EventArgs) Handles btnReset.Click
        textBoxT.Clear()
        lblT.Text = ""
        chkCF.Checked = False
        chkFC.Checked = False
        chkCK.Checked = False
        chkKC.Checked = False

    End Sub

    Private Sub btnClear_Click(sender As Object, e As EventArgs) Handles btnClear.Click
        textBoxUC.Clear()
        lblUC.Text = ""
        cmbUC.Text = "Choose one:"

    End Sub

    Private Sub multiply_Click(sender As Object, e As EventArgs) Handles multiply.Click
        If textBoxM.Text = "" Or textBoxM.Text = "." Then
            MessageBox.Show("Introduce a value to multiply!", "Value Required", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Return

        End If
        listBoxM.Items.Clear()

        Dim i As Integer

        For i = 1 To 12
            listBoxM.Items.Add(i & " x " & textBoxM.Text & " = " & i * textBoxM.Text)
        Next
    End Sub

    Private Sub reset_Click(sender As Object, e As EventArgs) Handles reset.Click
        listBoxM.Items.Clear()
        textBoxM.Clear()


    End Sub

    Private Sub button_Click(sender As Object, e As EventArgs) Handles btn9.Click, btn8.Click, btn7.Click, btn6.Click, btn5.Click, btn4.Click, btn3.Click, btn2.Click, btn1.Click, btn0.Click
        Dim b As Button = sender
        If textBoxSt.Text = "0" Then
            textBoxSt.Text = b.Text
        Else
            textBoxSt.Text = textBoxSt.Text + b.Text
        End If

    End Sub

    Private Sub arithmeticOp_Click(sender As Object, e As EventArgs) Handles btnPlus.Click, btnMul.Click, btnMinus.Click, btnDiv.Click, btnExp.Click, btnMod.Click, btnProc.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim o As Button = sender
        firstNumber = textBoxSt.Text

        lblSt.Text = textBoxSt.Text
        textBoxSt.Text = "0"
        operationA = o.Text
        lblSt.Text = lblSt.Text + " " + operationA

    End Sub

    Private Sub btnEq_Click(sender As Object, e As EventArgs) Handles btnEq.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If
        secondNumber = textBoxSt.Text

        If operationA = "+" Then
            result = firstNumber + secondNumber
            textBoxSt.Text = result
            lblSt.Text = ""
        ElseIf operationA = "-" Then
            result = firstNumber - secondNumber
            textBoxSt.Text = result
            lblSt.Text = ""
        ElseIf operationA = "*" Then
            result = firstNumber * secondNumber
            textBoxSt.Text = result
            lblSt.Text = ""
        ElseIf operationA = "/" Then
            result = firstNumber / secondNumber
            textBoxSt.Text = result
            lblSt.Text = ""
        ElseIf operationA = "Mod" Then
            result = firstNumber Mod secondNumber
            textBoxSt.Text = result
            lblSt.Text = ""
        ElseIf operationA = "Exp" Then
            result = firstNumber ^ secondNumber
            textBoxSt.Text = result
            lblSt.Text = ""
        ElseIf operationA = "%" Then
            result = (firstNumber / secondNumber) * 100
            textBoxSt.Text = result
            lblSt.Text = ""
        End If

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        If textBoxSt.Text.Length > 0 Then
            If textBoxSt.Text.Length = 1 Then
                textBoxSt.Text = "0"
                Return
            End If
            If textBoxSt.Text.Length = 2 Then
                If textBoxSt.Text.Contains(Chr(45)) Then
                    textBoxSt.Text = "0"
                    Return
                End If
            End If
                textBoxSt.Text = textBoxSt.Text.Remove(textBoxSt.Text.Length - 1, 1)

        End If
    End Sub

    Private Sub btnDt_Click(sender As Object, e As EventArgs) Handles btnDt.Click
        If InStr(textBoxSt.Text, ".") = 0 Then
            textBoxSt.Text = textBoxSt.Text + "."
        End If
    End Sub

    Private Sub btnCE_Click(sender As Object, e As EventArgs) Handles btnCE.Click
        textBoxSt.Text = "0"

    End Sub

    Private Sub btnC_Click(sender As Object, e As EventArgs) Handles btnC.Click
        textBoxSt.Text = "0"
        lblSt.Text = ""
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If
        textBoxSt.Text = (-1) * textBoxSt.Text

    End Sub

    Private Sub btnPi_Click(sender As Object, e As EventArgs) Handles btnPi.Click
        textBoxSt.Text = "3.14159265359"
    End Sub

    Private Sub btnLog_Click(sender As Object, e As EventArgs) Handles btnLog.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim log As Double
        log = Double.Parse(textBoxSt.Text)
        lblSt.Text = System.Convert.ToString("log (" + textBoxSt.Text + ")")
        log = Math.Log10(log)
        textBoxSt.Text = System.Convert.ToString(log)

    End Sub

    Private Sub btnSqrt_Click(sender As Object, e As EventArgs) Handles btnSqrt.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim aux As Double
        aux = Double.Parse(textBoxSt.Text)
        lblSt.Text = System.Convert.ToString("sqrt (" + textBoxSt.Text + ")")
        aux = Math.Sqrt(aux)
        textBoxSt.Text = System.Convert.ToString(aux)
    End Sub

    Private Sub btnSinh_Click(sender As Object, e As EventArgs) Handles btnSinh.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim aux As Double
        aux = Double.Parse(textBoxSt.Text)
        lblSt.Text = System.Convert.ToString("sinh (" + textBoxSt.Text + ")")
        aux = Math.Sinh(aux)
        textBoxSt.Text = System.Convert.ToString(aux)
    End Sub

    Private Sub btnCosh_Click(sender As Object, e As EventArgs) Handles btnCosh.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim aux As Double
        aux = Double.Parse(textBoxSt.Text)
        lblSt.Text = System.Convert.ToString("cosh (" + textBoxSt.Text + ")")
        aux = Math.Cosh(aux)
        textBoxSt.Text = System.Convert.ToString(aux)
    End Sub

    Private Sub btnTanh_Click(sender As Object, e As EventArgs) Handles btnTanh.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim aux As Double
        aux = Double.Parse(textBoxSt.Text)
        lblSt.Text = System.Convert.ToString("tanh (" + textBoxSt.Text + ")")
        aux = Math.Tanh(aux)
        textBoxSt.Text = System.Convert.ToString(aux)
    End Sub

    Private Sub btnSin_Click(sender As Object, e As EventArgs) Handles btnSin.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim aux As Double
        aux = Double.Parse(textBoxSt.Text)
        lblSt.Text = System.Convert.ToString("sin (" + textBoxSt.Text + ")")
        aux = Math.Sin(aux)
        textBoxSt.Text = System.Convert.ToString(aux)
    End Sub

    Private Sub btnCos_Click(sender As Object, e As EventArgs) Handles btnCos.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim aux As Double
        aux = Double.Parse(textBoxSt.Text)
        lblSt.Text = System.Convert.ToString("cos (" + textBoxSt.Text + ")")
        aux = Math.Cos(aux)
        textBoxSt.Text = System.Convert.ToString(aux)
    End Sub

    Private Sub btnTan_Click(sender As Object, e As EventArgs) Handles btnTan.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim aux As Double
        aux = Double.Parse(textBoxSt.Text)
        lblSt.Text = System.Convert.ToString("tan (" + textBoxSt.Text + ")")
        aux = Math.Tan(aux)
        textBoxSt.Text = System.Convert.ToString(aux)
    End Sub

    Private Sub btnBin_Click(sender As Object, e As EventArgs) Handles btnBin.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Try
            textBoxSt.Text = System.Convert.ToString(Integer.Parse(textBoxSt.Text), 2)
        Catch ex As System.FormatException
            textBoxSt.Text = "Wrong input format!"
            Return
        Catch ex As System.OverflowException
            textBoxSt.Text = "The value is too big to convert!"
            Return

        End Try

    End Sub

    Private Sub btnHex_Click(sender As Object, e As EventArgs) Handles btnHex.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Try
            textBoxSt.Text = System.Convert.ToString(Integer.Parse(textBoxSt.Text), 16)
        Catch ex As System.FormatException
            textBoxSt.Text = "Wrong input format!"
            Return

        End Try
    End Sub

    Private Sub btnOct_Click(sender As Object, e As EventArgs) Handles btnOct.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Try
            textBoxSt.Text = System.Convert.ToString(Integer.Parse(textBoxSt.Text), 8)
        Catch ex As System.FormatException
            textBoxSt.Text = "Wrong input format!"
            Return
        Catch ex As System.OverflowException
            textBoxSt.Text = "The value is too big to convert!"
            Return

        End Try
    End Sub

    Private Sub btnln_Click(sender As Object, e As EventArgs) Handles btnln.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim log As Double
        log = Double.Parse(textBoxSt.Text)
        lblSt.Text = System.Convert.ToString("ln (" + textBoxSt.Text + ")")
        log = Math.Log(log)
        textBoxSt.Text = System.Convert.ToString(log)

    End Sub

    Private Sub btnSq_Click(sender As Object, e As EventArgs) Handles btnSq.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        lblSt.Text = System.Convert.ToString(textBoxSt.Text + " ^ 2")
        textBoxSt.Text = System.Convert.ToString(Double.Parse(textBoxSt.Text) ^ 2)
    End Sub

    Private Sub btnCube_Click(sender As Object, e As EventArgs) Handles btnCube.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        lblSt.Text = System.Convert.ToString(textBoxSt.Text + " ^ 3")
        textBoxSt.Text = System.Convert.ToString(Double.Parse(textBoxSt.Text) ^ 3)
    End Sub

    Private Sub btnInv_Click(sender As Object, e As EventArgs) Handles btnInv.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        lblSt.Text = System.Convert.ToString(textBoxSt.Text + " ^ (-1)")
        textBoxSt.Text = System.Convert.ToString(Double.Parse(textBoxSt.Text) ^ (-1))
    End Sub

    Private Sub textBoxSt_KeyPress(sender As Object, e As KeyPressEventArgs) Handles textBoxSt.KeyPress
        If Asc(e.KeyChar) = 8 Then
            If textBoxSt.Text.Length = 2 And textBoxSt.Text.Contains(Chr(45)) Then
                textBoxSt.Text = "0"
                Return
            End If

            If textBoxSt.Text.Length = 1 Or textBoxSt.Text.Length = 0 Then
                textBoxSt.Text = "0"
                Return
            End If
            Return
        End If

        If Asc(e.KeyChar) = 46 Then
            If textBoxSt.Text.Contains(Chr(46)) Then
                e.Handled = True
                Return
            End If
            Return
        End If

        If Asc(e.KeyChar) <> 8 And Not (Asc(e.KeyChar) = 13) Then

            If Asc(e.KeyChar) < 48 Or Asc(e.KeyChar) > 57 Then
                e.Handled = True

            End If
        End If
    End Sub

    Private Sub textBoxT_KeyPress(sender As Object, e As KeyPressEventArgs) Handles textBoxT.KeyPress
        If Asc(e.KeyChar) = 8 Then
            If textBoxT.Text.Length = 2 And textBoxT.Text.Contains(Chr(45)) Then
                textBoxT.Text = "0"
                Return
            End If

            If textBoxT.Text.Length = 1 Or textBoxT.Text.Length = 0 Then
                textBoxT.Text = "0"
                Return
            End If
            Return
        End If

        If Asc(e.KeyChar) = 46 Then
            If textBoxT.Text.Contains(Chr(46)) Then
                e.Handled = True
                Return
            End If
            Return
        End If

        If Asc(e.KeyChar) <> 8 And Not (Asc(e.KeyChar) = 13) Then

            If Asc(e.KeyChar) < 48 Or Asc(e.KeyChar) > 57 Then
                e.Handled = True

            End If
        End If
    End Sub

    Private Sub textBoxM_KeyPress(sender As Object, e As KeyPressEventArgs) Handles textBoxM.KeyPress
        If Asc(e.KeyChar) = 8 Then
            If textBoxM.Text.Length = 2 And textBoxM.Text.Contains(Chr(45)) Then
                textBoxM.Text = "0"
                Return
            End If

            If textBoxM.Text.Length = 1 Or textBoxM.Text.Length = 0 Then
                textBoxM.Text = "0"
                Return
            End If
            Return
        End If

        If Asc(e.KeyChar) = 46 Then
            If textBoxM.Text.Contains(Chr(46)) Then
                e.Handled = True
                Return
            End If
            Return
        End If

        If Asc(e.KeyChar) <> 8 And Not (Asc(e.KeyChar) = 13) Then

            If Asc(e.KeyChar) < 48 Or Asc(e.KeyChar) > 57 Then
                e.Handled = True

            End If
        End If
    End Sub

    Private Sub textBoxUC_KeyPress(sender As Object, e As KeyPressEventArgs) Handles textBoxUC.KeyPress
        If Asc(e.KeyChar) = 8 Then
            If textBoxUC.Text.Length = 2 And textBoxUC.Text.Contains(Chr(45)) Then
                textBoxUC.Text = "0"
                Return
            End If

            If textBoxUC.Text.Length = 1 Or textBoxUC.Text.Length = 0 Then
                textBoxUC.Text = "0"
                Return
            End If
            Return
        End If

        If Asc(e.KeyChar) = 46 Then
            If textBoxUC.Text.Contains(Chr(46)) Then
                e.Handled = True
                Return
            End If
            Return
        End If

        If Asc(e.KeyChar) <> 8 And Not (Asc(e.KeyChar) = 13) Then

            If Asc(e.KeyChar) < 48 Or Asc(e.KeyChar) > 57 Then
                e.Handled = True

            End If
        End If
    End Sub


    Private Sub btnFac_Click(sender As Object, e As EventArgs) Handles btnFac.Click
        If (wrongInputFormat(textBoxSt) = False) Then
            Return
        End If

        Dim fac As Double
        Dim n As Long
        fac = 1

        Try
            n = Long.Parse(textBoxSt.Text)
        Catch ex As System.FormatException
            textBoxSt.Text = "Wrong input format!"
            Return

        End Try

        If n >= 171 Then
            textBoxSt.Text = "Infinite!"
            Return
        End If

        If n < 0 Then
            MessageBox.Show("Introduce a non-negative value!", "Wrong Value", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Return
        ElseIf n = 0 Then
            fac = 1
        ElseIf n > 0 Then
            For i = 1 To n
                fac = fac * i
            Next
        End If
        lblSt.Text = System.Convert.ToString(textBoxSt.Text + "!")
        textBoxSt.Text = System.Convert.ToString(fac)


    End Sub

    Private Sub UnitConversionToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles UnitConversionToolStripMenuItem.Click
        Me.Width = 835
        textBoxSt.Width = 460
        Me.Text = "Unit Conversion"
        GroupBox4.Location = New Point(496, 32)
        GroupBox1.Visible = False
        GroupBox3.Visible = False
        GroupBox4.Visible = True

    End Sub

    Private Sub ExitToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ExitToolStripMenuItem.Click
        Application.Exit()
    End Sub

    Private Sub ExitToolStripMenuItem1_Click(sender As Object, e As EventArgs) Handles ExitToolStripMenuItem1.Click
        Application.Exit()
    End Sub

    Private Sub convert_Click(sender As Object, e As EventArgs) Handles convertUC.Click
        If textBoxUC.Text = "" Or textBoxUC.Text = "." Then
            MessageBox.Show("Introduce a value to convert!", "Value Required", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Return

        End If

        Dim convert As Double
        If cmbUC.Text = "Kilometers to Miles" Then
            convert = (textBoxUC.Text / 1.609344)
            lblUC.Text = (convert) & "  Mi"
        ElseIf cmbUC.Text = "Miles to Kilometers" Then
            convert = (textBoxUC.Text * 1.609344)
            lblUC.Text = (convert) & "  Km"
        ElseIf cmbUC.Text = "Kilograms to LBS" Then
            convert = (textBoxUC.Text * 2.2046)
            lblUC.Text = (convert) & "  LBS"
        ElseIf cmbUC.Text = "LBS to Kilograms" Then
            convert = (textBoxUC.Text / 2.2046)
            lblUC.Text = (convert) & "  Kg"
        Else
            MessageBox.Show("Select a Conversion Mode!", "Unit Conversion", MessageBoxButtons.OK, MessageBoxIcon.Information)
        End If

    End Sub

    Private Function wrongInputFormat(b As TextBox) As Boolean
        If b.Text.Length = 0 Then
            b.Text = "0"
        End If

        If b.Text = "." Then
            b.Text = "0"
        End If

        For i = 0 To 127
            If i = 43 Then
                i = 44
            End If

            If i = 45 Then
                i = 47
            End If
            If i = 48 Then
                i = 58
            End If
            If i = 69 Then
                i = 70
            End If
            If (b.Text.Contains(Chr(i))) Then
                b.Text = "Wrong input format!"
                Return False

            End If
        Next
        Return True
    End Function

End Class
