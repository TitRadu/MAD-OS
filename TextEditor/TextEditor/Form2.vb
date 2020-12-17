Public Class Form2


    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Me.CenterToScreen()


    End Sub



    Private Sub NextButton_Click(sender As Object, e As EventArgs) Handles nextButton.Click
        Form1.SearchNextToolStripMenuItem.PerformClick()
        Me.Close()

    End Sub

    Private Sub PreviousButton_Click(sender As Object, e As EventArgs) Handles previousButton.Click
        Form1.SearchPreviousToolStripMenuItem.PerformClick()
        Me.Close()

    End Sub

End Class