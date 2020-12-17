<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form2
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.nextButton = New System.Windows.Forms.Button()
        Me.previousButton = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.searchText = New System.Windows.Forms.TextBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.replaceText = New System.Windows.Forms.TextBox()
        Me.SuspendLayout()
        '
        'nextButton
        '
        Me.nextButton.Location = New System.Drawing.Point(201, 40)
        Me.nextButton.Margin = New System.Windows.Forms.Padding(2)
        Me.nextButton.Name = "nextButton"
        Me.nextButton.Size = New System.Drawing.Size(71, 43)
        Me.nextButton.TabIndex = 0
        Me.nextButton.Text = "Next"
        Me.nextButton.UseVisualStyleBackColor = True
        '
        'previousButton
        '
        Me.previousButton.Location = New System.Drawing.Point(201, 204)
        Me.previousButton.Margin = New System.Windows.Forms.Padding(2)
        Me.previousButton.Name = "previousButton"
        Me.previousButton.Size = New System.Drawing.Size(71, 44)
        Me.previousButton.TabIndex = 1
        Me.previousButton.Text = "Previous"
        Me.previousButton.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.Font = New System.Drawing.Font("Trebuchet MS", 9.0!)
        Me.Label1.Location = New System.Drawing.Point(2, 110)
        Me.Label1.Margin = New System.Windows.Forms.Padding(2, 0, 2, 0)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(157, 19)
        Me.Label1.TabIndex = 2
        Me.Label1.Text = "Introduce a search string:"
        '
        'searchText
        '
        Me.searchText.Font = New System.Drawing.Font("Trebuchet MS", 10.2!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.searchText.Location = New System.Drawing.Point(179, 106)
        Me.searchText.Margin = New System.Windows.Forms.Padding(2)
        Me.searchText.Name = "searchText"
        Me.searchText.Size = New System.Drawing.Size(109, 23)
        Me.searchText.TabIndex = 3
        '
        'Label2
        '
        Me.Label2.Font = New System.Drawing.Font("Trebuchet MS", 9.0!)
        Me.Label2.Location = New System.Drawing.Point(2, 155)
        Me.Label2.Margin = New System.Windows.Forms.Padding(2, 0, 2, 0)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(166, 19)
        Me.Label2.TabIndex = 4
        Me.Label2.Text = "Introduce a replace string:"
        '
        'replaceText
        '
        Me.replaceText.Font = New System.Drawing.Font("Trebuchet MS", 10.2!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.replaceText.Location = New System.Drawing.Point(179, 151)
        Me.replaceText.Margin = New System.Windows.Forms.Padding(2)
        Me.replaceText.Name = "replaceText"
        Me.replaceText.Size = New System.Drawing.Size(109, 23)
        Me.replaceText.TabIndex = 5
        '
        'Form2
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(301, 271)
        Me.Controls.Add(Me.replaceText)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.searchText)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.previousButton)
        Me.Controls.Add(Me.nextButton)
        Me.Margin = New System.Windows.Forms.Padding(2)
        Me.Name = "Form2"
        Me.Text = "Form2"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents nextButton As Button
    Friend WithEvents previousButton As Button
    Friend WithEvents Label1 As Label
    Friend WithEvents searchText As TextBox
    Friend WithEvents Label2 As Label
    Friend WithEvents replaceText As TextBox
End Class
