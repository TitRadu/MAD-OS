<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
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
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.displayText = New System.Windows.Forms.RichTextBox()
        Me.FileToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NewToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NewEditorToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripSeparator1 = New System.Windows.Forms.ToolStripSeparator()
        Me.OpenToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SaveAsToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SaveToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripSeparator2 = New System.Windows.Forms.ToolStripSeparator()
        Me.ExitToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.EditToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.UndoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.RedoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SelectAllToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ClearToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripSeparator3 = New System.Windows.Forms.ToolStripSeparator()
        Me.CutToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CopyToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.PasteToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripSeparator4 = New System.Windows.Forms.ToolStripSeparator()
        Me.SearchNextToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SearchPreviousToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SearchToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ReplaceAllToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ReplaceToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SearchAllToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ViewToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ZoomToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ZoomInToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ZoomOutToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.RestoreToDefaultToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CodeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.FreeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog()
        Me.SaveFileDialog1 = New System.Windows.Forms.SaveFileDialog()
        Me.informationText = New System.Windows.Forms.Label()
        Me.languageSelector = New System.Windows.Forms.Label()
        Me.MenuStrip1.SuspendLayout()
        Me.SuspendLayout()
        '
        'displayText
        '
        Me.displayText.AcceptsTab = True
        Me.displayText.Dock = System.Windows.Forms.DockStyle.Fill
        Me.displayText.Font = New System.Drawing.Font("Consolas", 11.0!)
        Me.displayText.Location = New System.Drawing.Point(0, 30)
        Me.displayText.Margin = New System.Windows.Forms.Padding(2)
        Me.displayText.Name = "displayText"
        Me.displayText.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedBoth
        Me.displayText.Size = New System.Drawing.Size(664, 339)
        Me.displayText.TabIndex = 1
        Me.displayText.Text = ""
        Me.displayText.WordWrap = False
        '
        'FileToolStripMenuItem
        '
        Me.FileToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.NewToolStripMenuItem, Me.NewEditorToolStripMenuItem, Me.ToolStripSeparator1, Me.OpenToolStripMenuItem, Me.SaveAsToolStripMenuItem, Me.SaveToolStripMenuItem, Me.ToolStripSeparator2, Me.ExitToolStripMenuItem})
        Me.FileToolStripMenuItem.Name = "FileToolStripMenuItem"
        Me.FileToolStripMenuItem.Size = New System.Drawing.Size(46, 26)
        Me.FileToolStripMenuItem.Text = "File"
        '
        'NewToolStripMenuItem
        '
        Me.NewToolStripMenuItem.Name = "NewToolStripMenuItem"
        Me.NewToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.N), System.Windows.Forms.Keys)
        Me.NewToolStripMenuItem.Size = New System.Drawing.Size(259, 26)
        Me.NewToolStripMenuItem.Text = "New"
        '
        'NewEditorToolStripMenuItem
        '
        Me.NewEditorToolStripMenuItem.Name = "NewEditorToolStripMenuItem"
        Me.NewEditorToolStripMenuItem.ShortcutKeys = CType(((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.Shift) _
            Or System.Windows.Forms.Keys.N), System.Windows.Forms.Keys)
        Me.NewEditorToolStripMenuItem.Size = New System.Drawing.Size(259, 26)
        Me.NewEditorToolStripMenuItem.Text = "New Editor"
        '
        'ToolStripSeparator1
        '
        Me.ToolStripSeparator1.Name = "ToolStripSeparator1"
        Me.ToolStripSeparator1.Size = New System.Drawing.Size(256, 6)
        '
        'OpenToolStripMenuItem
        '
        Me.OpenToolStripMenuItem.Name = "OpenToolStripMenuItem"
        Me.OpenToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.O), System.Windows.Forms.Keys)
        Me.OpenToolStripMenuItem.Size = New System.Drawing.Size(259, 26)
        Me.OpenToolStripMenuItem.Text = "Open"
        '
        'SaveAsToolStripMenuItem
        '
        Me.SaveAsToolStripMenuItem.Name = "SaveAsToolStripMenuItem"
        Me.SaveAsToolStripMenuItem.ShortcutKeys = CType(((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.Shift) _
            Or System.Windows.Forms.Keys.S), System.Windows.Forms.Keys)
        Me.SaveAsToolStripMenuItem.Size = New System.Drawing.Size(259, 26)
        Me.SaveAsToolStripMenuItem.Text = "Save as"
        '
        'SaveToolStripMenuItem
        '
        Me.SaveToolStripMenuItem.Name = "SaveToolStripMenuItem"
        Me.SaveToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.S), System.Windows.Forms.Keys)
        Me.SaveToolStripMenuItem.Size = New System.Drawing.Size(259, 26)
        Me.SaveToolStripMenuItem.Text = "Save"
        '
        'ToolStripSeparator2
        '
        Me.ToolStripSeparator2.Name = "ToolStripSeparator2"
        Me.ToolStripSeparator2.Size = New System.Drawing.Size(256, 6)
        '
        'ExitToolStripMenuItem
        '
        Me.ExitToolStripMenuItem.Name = "ExitToolStripMenuItem"
        Me.ExitToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.E), System.Windows.Forms.Keys)
        Me.ExitToolStripMenuItem.Size = New System.Drawing.Size(259, 26)
        Me.ExitToolStripMenuItem.Text = "Exit"
        '
        'MenuStrip1
        '
        Me.MenuStrip1.BackColor = System.Drawing.SystemColors.Window
        Me.MenuStrip1.ImageScalingSize = New System.Drawing.Size(20, 20)
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FileToolStripMenuItem, Me.EditToolStripMenuItem, Me.ViewToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Padding = New System.Windows.Forms.Padding(4, 2, 0, 2)
        Me.MenuStrip1.Size = New System.Drawing.Size(664, 30)
        Me.MenuStrip1.TabIndex = 0
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'EditToolStripMenuItem
        '
        Me.EditToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.UndoToolStripMenuItem, Me.RedoToolStripMenuItem, Me.SelectAllToolStripMenuItem, Me.ClearToolStripMenuItem, Me.ToolStripSeparator3, Me.CutToolStripMenuItem, Me.CopyToolStripMenuItem, Me.PasteToolStripMenuItem, Me.ToolStripSeparator4, Me.SearchNextToolStripMenuItem, Me.SearchPreviousToolStripMenuItem, Me.SearchToolStripMenuItem, Me.ReplaceAllToolStripMenuItem, Me.ReplaceToolStripMenuItem, Me.SearchAllToolStripMenuItem})
        Me.EditToolStripMenuItem.Name = "EditToolStripMenuItem"
        Me.EditToolStripMenuItem.Size = New System.Drawing.Size(49, 26)
        Me.EditToolStripMenuItem.Text = "Edit"
        '
        'UndoToolStripMenuItem
        '
        Me.UndoToolStripMenuItem.Name = "UndoToolStripMenuItem"
        Me.UndoToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.Z), System.Windows.Forms.Keys)
        Me.UndoToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.UndoToolStripMenuItem.Text = "Undo"
        '
        'RedoToolStripMenuItem
        '
        Me.RedoToolStripMenuItem.Name = "RedoToolStripMenuItem"
        Me.RedoToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.Y), System.Windows.Forms.Keys)
        Me.RedoToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.RedoToolStripMenuItem.Text = "Redo"
        '
        'SelectAllToolStripMenuItem
        '
        Me.SelectAllToolStripMenuItem.Name = "SelectAllToolStripMenuItem"
        Me.SelectAllToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.A), System.Windows.Forms.Keys)
        Me.SelectAllToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.SelectAllToolStripMenuItem.Text = "Select All"
        '
        'ClearToolStripMenuItem
        '
        Me.ClearToolStripMenuItem.Name = "ClearToolStripMenuItem"
        Me.ClearToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.Q), System.Windows.Forms.Keys)
        Me.ClearToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.ClearToolStripMenuItem.Text = "Clear"
        '
        'ToolStripSeparator3
        '
        Me.ToolStripSeparator3.Name = "ToolStripSeparator3"
        Me.ToolStripSeparator3.Size = New System.Drawing.Size(216, 6)
        '
        'CutToolStripMenuItem
        '
        Me.CutToolStripMenuItem.Name = "CutToolStripMenuItem"
        Me.CutToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.X), System.Windows.Forms.Keys)
        Me.CutToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.CutToolStripMenuItem.Text = "Cut"
        '
        'CopyToolStripMenuItem
        '
        Me.CopyToolStripMenuItem.Name = "CopyToolStripMenuItem"
        Me.CopyToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.C), System.Windows.Forms.Keys)
        Me.CopyToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.CopyToolStripMenuItem.Text = "Copy"
        '
        'PasteToolStripMenuItem
        '
        Me.PasteToolStripMenuItem.Name = "PasteToolStripMenuItem"
        Me.PasteToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.V), System.Windows.Forms.Keys)
        Me.PasteToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.PasteToolStripMenuItem.Text = "Paste"
        '
        'ToolStripSeparator4
        '
        Me.ToolStripSeparator4.Name = "ToolStripSeparator4"
        Me.ToolStripSeparator4.Size = New System.Drawing.Size(216, 6)
        '
        'SearchNextToolStripMenuItem
        '
        Me.SearchNextToolStripMenuItem.Name = "SearchNextToolStripMenuItem"
        Me.SearchNextToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F1
        Me.SearchNextToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.SearchNextToolStripMenuItem.Text = "Search Next"
        '
        'SearchPreviousToolStripMenuItem
        '
        Me.SearchPreviousToolStripMenuItem.Name = "SearchPreviousToolStripMenuItem"
        Me.SearchPreviousToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F2
        Me.SearchPreviousToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.SearchPreviousToolStripMenuItem.Text = "Search Previous"
        '
        'SearchToolStripMenuItem
        '
        Me.SearchToolStripMenuItem.Name = "SearchToolStripMenuItem"
        Me.SearchToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.F), System.Windows.Forms.Keys)
        Me.SearchToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.SearchToolStripMenuItem.Text = "Search"
        '
        'ReplaceAllToolStripMenuItem
        '
        Me.ReplaceAllToolStripMenuItem.Name = "ReplaceAllToolStripMenuItem"
        Me.ReplaceAllToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.T), System.Windows.Forms.Keys)
        Me.ReplaceAllToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.ReplaceAllToolStripMenuItem.Text = "Replace All"
        '
        'ReplaceToolStripMenuItem
        '
        Me.ReplaceToolStripMenuItem.Name = "ReplaceToolStripMenuItem"
        Me.ReplaceToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.R), System.Windows.Forms.Keys)
        Me.ReplaceToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.ReplaceToolStripMenuItem.Text = "Replace"
        '
        'SearchAllToolStripMenuItem
        '
        Me.SearchAllToolStripMenuItem.Name = "SearchAllToolStripMenuItem"
        Me.SearchAllToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Alt Or System.Windows.Forms.Keys.S), System.Windows.Forms.Keys)
        Me.SearchAllToolStripMenuItem.Size = New System.Drawing.Size(219, 26)
        Me.SearchAllToolStripMenuItem.Text = "Search All"
        '
        'ViewToolStripMenuItem
        '
        Me.ViewToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ZoomToolStripMenuItem, Me.CodeToolStripMenuItem})
        Me.ViewToolStripMenuItem.Name = "ViewToolStripMenuItem"
        Me.ViewToolStripMenuItem.Size = New System.Drawing.Size(55, 26)
        Me.ViewToolStripMenuItem.Text = "View"
        '
        'ZoomToolStripMenuItem
        '
        Me.ZoomToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ZoomInToolStripMenuItem, Me.ZoomOutToolStripMenuItem, Me.RestoreToDefaultToolStripMenuItem})
        Me.ZoomToolStripMenuItem.Name = "ZoomToolStripMenuItem"
        Me.ZoomToolStripMenuItem.Size = New System.Drawing.Size(132, 26)
        Me.ZoomToolStripMenuItem.Text = "Zoom"
        '
        'ZoomInToolStripMenuItem
        '
        Me.ZoomInToolStripMenuItem.Name = "ZoomInToolStripMenuItem"
        Me.ZoomInToolStripMenuItem.Size = New System.Drawing.Size(213, 26)
        Me.ZoomInToolStripMenuItem.Text = "Zoom In"
        '
        'ZoomOutToolStripMenuItem
        '
        Me.ZoomOutToolStripMenuItem.Name = "ZoomOutToolStripMenuItem"
        Me.ZoomOutToolStripMenuItem.Size = New System.Drawing.Size(213, 26)
        Me.ZoomOutToolStripMenuItem.Text = "Zoom Out"
        '
        'RestoreToDefaultToolStripMenuItem
        '
        Me.RestoreToDefaultToolStripMenuItem.Name = "RestoreToDefaultToolStripMenuItem"
        Me.RestoreToDefaultToolStripMenuItem.Size = New System.Drawing.Size(213, 26)
        Me.RestoreToDefaultToolStripMenuItem.Text = "Restore to Default"
        '
        'CodeToolStripMenuItem
        '
        Me.CodeToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FreeToolStripMenuItem, Me.CToolStripMenuItem})
        Me.CodeToolStripMenuItem.Name = "CodeToolStripMenuItem"
        Me.CodeToolStripMenuItem.Size = New System.Drawing.Size(132, 26)
        Me.CodeToolStripMenuItem.Text = "Code"
        '
        'FreeToolStripMenuItem
        '
        Me.FreeToolStripMenuItem.Name = "FreeToolStripMenuItem"
        Me.FreeToolStripMenuItem.Size = New System.Drawing.Size(120, 26)
        Me.FreeToolStripMenuItem.Text = "Free"
        '
        'CToolStripMenuItem
        '
        Me.CToolStripMenuItem.Name = "CToolStripMenuItem"
        Me.CToolStripMenuItem.Size = New System.Drawing.Size(120, 26)
        Me.CToolStripMenuItem.Text = "C"
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.FileName = "OpenFileDialog1"
        '
        'informationText
        '
        Me.informationText.Location = New System.Drawing.Point(2, 334)
        Me.informationText.Name = "informationText"
        Me.informationText.Size = New System.Drawing.Size(644, 17)
        Me.informationText.TabIndex = 2
        Me.informationText.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'languageSelector
        '
        Me.languageSelector.Font = New System.Drawing.Font("Trebuchet MS", 10.0!)
        Me.languageSelector.Location = New System.Drawing.Point(588, 6)
        Me.languageSelector.Name = "languageSelector"
        Me.languageSelector.Size = New System.Drawing.Size(76, 18)
        Me.languageSelector.TabIndex = 3
        Me.languageSelector.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 18.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(664, 369)
        Me.Controls.Add(Me.languageSelector)
        Me.Controls.Add(Me.informationText)
        Me.Controls.Add(Me.displayText)
        Me.Controls.Add(Me.MenuStrip1)
        Me.Font = New System.Drawing.Font("Trebuchet MS", 8.0!)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Margin = New System.Windows.Forms.Padding(2)
        Me.Name = "Form1"
        Me.Text = "Untitled -MADITOR"
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents displayText As RichTextBox
    Friend WithEvents FileToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents OpenToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SaveAsToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SaveToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents MenuStrip1 As MenuStrip
    Friend WithEvents OpenFileDialog1 As OpenFileDialog
    Friend WithEvents SaveFileDialog1 As SaveFileDialog
    Friend WithEvents NewToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents NewEditorToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripSeparator1 As ToolStripSeparator
    Friend WithEvents ToolStripSeparator2 As ToolStripSeparator
    Friend WithEvents ExitToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents EditToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents UndoToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents RedoToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SelectAllToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ClearToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripSeparator3 As ToolStripSeparator
    Friend WithEvents ViewToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ZoomToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ZoomInToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ZoomOutToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents RestoreToDefaultToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents CutToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents CopyToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents PasteToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripSeparator4 As ToolStripSeparator
    Friend WithEvents SearchNextToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SearchPreviousToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents informationText As Label
    Friend WithEvents SearchToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ReplaceAllToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ReplaceToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents CodeToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents CToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents FreeToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents languageSelector As Label
    Friend WithEvents SearchAllToolStripMenuItem As ToolStripMenuItem
End Class
