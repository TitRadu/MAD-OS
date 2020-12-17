Imports System.IO
Imports System.Text.RegularExpressions



Public Class Form1
    Dim control As String
    Dim defaultZoom As Double
    Dim startIndex As Integer
    Dim reverseStartIndex As Integer
    Dim parse As Integer
    ReadOnly SearchForm As New Form2
    Dim oldSizeHeight As New Integer
    Dim oldSizeWidth As New Integer
    Dim originalSelectionStart As New Integer
    Dim originalSelectionLength As New Integer
    Dim originalColor As New Color
    Dim time As Integer 'Un intreg ce va tine minte istoricul display-ului.
    ReadOnly history As New List(Of String) 'aici vom retine istoricul display-ului.




    Private Sub OpenToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles OpenToolStripMenuItem.Click
        Dim fileName As String
        If OpenFileDialog1.ShowDialog() <> DialogResult.OK Then
            Return
        End If
        fileName = OpenFileDialog1.FileName
        Me.Text = fileName
        Dim streamReader As New StreamReader(fileName)
        displayText.Text = streamReader.ReadToEnd()
        streamReader.Close()
        Me.Text = Me.Text.Remove(Me.Text.Length - 1, 1)
        control = "Open"

    End Sub

    Private Sub SaveAsToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SaveAsToolStripMenuItem.Click
        Dim fileName As String
        If SaveFileDialog1.ShowDialog() <> DialogResult.OK Then
            Return
        End If
        fileName = SaveFileDialog1.FileName
        Me.Text = fileName
        Dim streamWriter As New StreamWriter(fileName)
        streamWriter.Write(displayText.Text)
        streamWriter.Close()
        control = "SaveAs"
    End Sub

    Private Sub SaveToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SaveToolStripMenuItem.Click
        Dim fileName As String


        If control = "Open" Then
            fileName = OpenFileDialog1.FileName
        Else
            fileName = SaveFileDialog1.FileName
        End If

        Try
            Dim streamWriter As New StreamWriter(fileName)
            streamWriter.Write(displayText.Text)
            streamWriter.Close()
        Catch ex As ArgumentException
            MessageBox.Show("You didn't open any file!", "File missing!", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Return
        End Try
        If Me.Text.Contains(Chr(42)) Then
            Me.Text = Me.Text.Remove(Me.Text.Length - 1, 1)
        End If


    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Me.CenterToScreen()
        Me.Text = "Untitled -MADITOR"
        startIndex = 0
        reverseStartIndex = 0
        defaultZoom = displayText.ZoomFactor
        OpenFileDialog1.Reset()
        SaveFileDialog1.Reset()
        SaveFileDialog1.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*"
        OpenFileDialog1.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*"
        oldSizeHeight = Me.Size.Height
        oldSizeWidth = Me.Size.Width
        languageSelector.Text = "Free"
        originalColor = displayText.ForeColor
        time = 0

    End Sub

    Private Sub NewToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NewToolStripMenuItem.Click
        Me.Text = "Untitled -MADITOR"
        OpenFileDialog1.Reset()
        SaveFileDialog1.Reset()

    End Sub

    Private Sub RichTextBox1_TextChanged(sender As Object, e As EventArgs) Handles displayText.TextChanged
        
        originalSelectionStart = displayText.SelectionStart
        originalSelectionLength = displayText.SelectionLength

        If languageSelector.Text = "Free" Then
            FreeToolStripMenuItem.PerformClick()

        ElseIf languageSelector.Text = "C" Then
            CToolStripMenuItem.PerformClick()

        End If


        If Me.Text <> "Untitled -MADITOR" And Me.Text.Contains(Chr(42)) = False Then
            Me.Text += "*"
        End If
        startIndex = displayText.SelectionStart()
        reverseStartIndex = displayText.Text.Length - startIndex
        informationText.Text = "Col:" & (displayText.SelectionStart() - displayText.GetFirstCharIndexOfCurrentLine + 1) & " Line:" & (displayText.GetLineFromCharIndex(displayText.SelectionStart) + 1) & " | " & displayText.Text.Length & " Characters " & displayText.Lines.Length & " Lines"

    End Sub

    Private Sub NewEditorToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NewEditorToolStripMenuItem.Click
        Process.Start("TextEditor.exe")

    End Sub

    Private Sub ExitToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ExitToolStripMenuItem.Click
        Application.Exit()

    End Sub

    Private Sub UndoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles UndoToolStripMenuItem.Click
        'In Undo ne vom intoarce in istoric cu 1 pas.
        If time >= 1 Then
            time -= 1
        End If

        If history.LongCount > 0 Then
            displayText.Text = history.ElementAt(time)
        End If



    End Sub

    Private Sub RedoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles RedoToolStripMenuItem.Click
        'In Redo ne vom duce in viitorul istoricului cu 1 pas.
        If time < history.LongCount Then
            time += 1
        End If


        displayText.Text = history.ElementAt(time - 1)

    End Sub

    Private Sub SelectAllToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SelectAllToolStripMenuItem.Click
        displayText.SelectAll()

    End Sub

    Private Sub ClearToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ClearToolStripMenuItem.Click
        displayText.Clear()
    End Sub

    Private Sub ZoomInToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ZoomInToolStripMenuItem.Click
        displayText.ZoomFactor = displayText.ZoomFactor + (1 / 10) * displayText.ZoomFactor

    End Sub

    Private Sub ZoomOutToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ZoomOutToolStripMenuItem.Click
        displayText.ZoomFactor = displayText.ZoomFactor - (1 / 10) * displayText.ZoomFactor

    End Sub

    Private Sub RestoreToDefaultToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles RestoreToDefaultToolStripMenuItem.Click
        displayText.ZoomFactor = defaultZoom


    End Sub

    Private Sub CutToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CutToolStripMenuItem.Click
        displayText.Cut()

    End Sub

    Private Sub CopyToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CopyToolStripMenuItem.Click
        displayText.Copy()
    End Sub

    Private Sub PasteToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles PasteToolStripMenuItem.Click
        displayText.Paste()

    End Sub

    Private Sub SearchNextToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SearchNextToolStripMenuItem.Click
        parse = displayText.Find(SearchForm.searchText.Text, startIndex, displayText.Text.Length, vbNull)
        If parse = -1 Or startIndex = displayText.Text.Length Then
            startIndex = 0
            MessageBox.Show("Search reach the text final!", "Text final reached!", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Else
            startIndex = startIndex + (parse - startIndex) + SearchForm.searchText.Text.Length
            reverseStartIndex = displayText.Text.Length - startIndex
        End If

    End Sub

    Private Sub SearchPreviousToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SearchPreviousToolStripMenuItem.Click
        Dim reverseDisplayText As String = Reverse(displayText.Text)
        Dim reverseSearchText As String = Reverse(SearchForm.searchText.Text)

        parse = reverseDisplayText.IndexOf(reverseSearchText, reverseStartIndex)
        If parse = -1 Then
            reverseStartIndex = 0
            MessageBox.Show("Search reach the text final!", "Text final reached!", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Else
            displayText.SelectionStart = displayText.Text.Length() - parse - SearchForm.searchText.Text.Length
            displayText.SelectionLength = SearchForm.searchText.Text.Length
            reverseStartIndex = reverseStartIndex + (parse - reverseStartIndex) + SearchForm.searchText.Text.Length
            startIndex = displayText.Text.Length - reverseStartIndex
        End If

    End Sub

    Function Reverse(value As String) As String
        Dim arr() As Char = value.ToCharArray()
        Array.Reverse(arr)
        Return New String(arr)

    End Function

    Private Sub DisplayText_Click(sender As Object, e As EventArgs) Handles displayText.Click
        If time >= 1 Then
            If displayText.Text <> history.ElementAt(time - 1) Then
                history.Add(displayText.Text)
                time += 1
            End If
        End If

        If time = 0 Then
            history.Add(displayText.Text)
            time += 1
        End If


        startIndex = displayText.SelectionStart()
        reverseStartIndex = displayText.Text.Length - startIndex
        informationText.Text = "Col:" & (displayText.SelectionStart() - displayText.GetFirstCharIndexOfCurrentLine + 1) & " Line:" & (displayText.GetLineFromCharIndex(displayText.SelectionStart) + 1) & " | " & displayText.Text.Length & " Characters " & displayText.Lines.Length & " Lines"
    End Sub

    Private Sub DisplayText_KeyDown(sender As Object, e As KeyEventArgs) Handles displayText.KeyDown
        If time >= 1 Then
            If displayText.Text <> history.ElementAt(time - 1) Then
                history.Add(displayText.Text)
                time += 1
            End If
        End If

        If time = 0 Then
            history.Add(displayText.Text)
            time += 1
        End If


        If e.KeyCode >= 37 And e.KeyCode <= 40 Then
            'Codul de mai jos este scris avand in vedere faptul ca in ultimul apel 
            'sunt afisate valorile pozitiilor de la penultimul apel.
            'S-a obtinut functionalitatea prin multe incercari..

            'Diferente dintre pozitia curenta si pozitia primului caracter de pe linia curenta
            'va da ca rezultat coloana curenta din linia curenta.+1 vine de la faptul ca 
            'inital se incepe cu indexul 0.
            Dim Col As Integer
            Col = displayText.SelectionStart() - displayText.GetFirstCharIndexOfCurrentLine + 1

            'Se obtine linia adaugand +1 din acelasi motiv ca si mai sus.
            Dim Line As Integer
            Line = displayText.GetLineFromCharIndex(displayText.SelectionStart) + 1
            Dim CharCount As Integer
            CharCount = displayText.Text.Length
            Dim LineCount As Integer
            LineCount = displayText.Lines.Length
            If e.KeyCode = 37 Then
                'Tratare colt stanga. Situatia in care apasam tasta cand suntem la inceputul fisierului.
                If Col - 1 = 0 Then
                    Col = 2
                End If
                'Col - 1 vine de la combaterea trecutului. Avem "-" pentru ca venim de la dreapta la stanga.
                informationText.Text = "Col:" & (Col - 1) & " Line:" & (Line) & " | " & (CharCount) & " Characters " & (LineCount) & " Lines"

            ElseIf e.KeyCode = 38 Then
                'Tratare prima linie. Situatia in care suntem pe prima linie si apasam tasta. 
                If Line - 1 = 0 Then
                    Line = 2
                End If
                'Line - 1 vine de la combaterea trecutului. Avem "-" pentru ca venim de jos in sus.
                informationText.Text = "Col:" & (Col) & " Line:" & (Line - 1) & " | " & (CharCount) & " Characters " & (LineCount) & " Lines"

            ElseIf e.KeyCode = 39 Then
                'Tratare sfarsit de fisier. Situatia in care suntem la sfarsitul fisierului si apasam tasta.
                ''   If displayText.SelectionStart() + 2 = CharCount Then
                ''   Col = CharCount - displayText.GetFirstCharIndexOfCurrentLine - 1
           '' End If

                'Col + 1 vine de la combaterea trecutului. Avem "+" pentru ca venim de la stanga la dreapta.
                informationText.Text = "Col:" & (Col + 1) & " Line:" & (Line) & " | " & (CharCount) & " Characters " & (LineCount) & " Lines"

            ElseIf e.KeyCode = 40 Then
                'Tratare ultima linie. Situatia in care suntem pe ultima linie si apasam tasta.
                If Line + 1 = LineCount + 1 Then
                    Line = LineCount - 1
                End If
                'Line + 1 vine de la combaterea trecutului. Avem "+" pentru ca venim de sus in jos.
                informationText.Text = "Col:" & (Col) & " Line:" & (Line + 1) & " | " & (CharCount) & " Characters " & (LineCount) & " Lines"
            End If
        End If

    End Sub

    Private Sub SearchToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SearchToolStripMenuItem.Click
        SearchForm.ShowDialog()

    End Sub

    Private Sub Form1_Resize(sender As Object, e As EventArgs) Handles MyBase.Resize
        'Acest tip de eveniment se declanseaza inainaintea evenimentului de Form.Load.
        informationText.Width = Me.Size.Width - 35 'Linia aceasta face ca elementul sa isi modifice si latimea odata cu modificarea dimensiunii Form-ului.
        Dim difTop As Integer
        difTop = Me.Size.Height - oldSizeHeight

        If Not difTop = Me.Size.Height Then
            displayText.Text = difTop
            informationText.Top = informationText.Top + difTop
            oldSizeHeight = Me.Size.Height
        End If

        Dim difLeft As Integer
        difLeft = Me.Size.Width - oldSizeWidth

        If Not difLeft = Me.Size.Width Then
            displayText.Text = difLeft
            languageSelector.Left = languageSelector.Left + difLeft
            oldSizeWidth = Me.Size.Width
        End If

    End Sub

    Private Sub ReplaceAllToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ReplaceAllToolStripMenuItem.Click
        Try
            displayText.Text = displayText.Text.Replace(SearchForm.searchText.Text, SearchForm.replaceText.Text)
        Catch ex As System.ArgumentException
            MessageBox.Show("Search Text is empty!", "Replace Text Empty", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Return
        End Try


    End Sub

    Private Sub ReplaceToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ReplaceToolStripMenuItem.Click
        Try
            displayText.SelectedText = displayText.SelectedText.Replace(displayText.SelectedText, SearchForm.replaceText.Text)
        Catch ex As System.ArgumentException
            MessageBox.Show("Selected Text is empty!", "Replace Text Empty", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Return
        End Try

    End Sub

    Private Sub FreeToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles FreeToolStripMenuItem.Click
        languageSelector.Text = "Free"
        LanguageSelector_TextChanged()

    End Sub

    Private Sub CToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CToolStripMenuItem.Click
        languageSelector.Text = "C"
        LanguageSelector_TextChanged()

    End Sub

    Private Sub LanguageSelector_TextChanged() Handles languageSelector.TextChanged

        'Observatie: Schimbarea culorii genereaza evenimentul TextChanged.

        languageSelector.Focus()

        If languageSelector.Text = "Free" Then
            displayText.SelectionStart = 0
            displayText.SelectionLength = displayText.Text.Length
            displayText.SelectionColor = originalColor
            displayText.ForeColor = originalColor


        ElseIf languageSelector.Text = "C" Then
            'Textul trebuie procesat de fiecare data pornind de la culoarea originala.
            displayText.SelectionStart = 0
            displayText.SelectionLength = displayText.Text.Length
            displayText.SelectionColor = originalColor
            displayText.ForeColor = originalColor

            Dim collect As MatchCollection

            'Cuvinte-cheie
            collect = Regex.Matches(displayText.Text, "case[^A-Za-z0-9]|switch[^A-Za-z0-9]|do[^A-Za-z0-9]|while[^A-Za-z0-9]|if[^A-Za-z0-9]|else[^A-Za-z0-9]|int[^A-Za-z0-9]|char[^A-Za-z0-9]|float[^A-Za-z0-9]|double[^A-Za-z0-9]|void[^A-Za-z0-9]|return[^A-Za-z0-9]")

            For Each m As Match In collect
                displayText.SelectionStart = m.Index
                displayText.SelectionLength = m.Length - 1
                If Not (displayText.SelectionColor = Color.BlueViolet) Then
                    displayText.SelectionColor = Color.BlueViolet

                End If


            Next

            'Paranteze+Etc
            collect = Regex.Matches(displayText.Text, "[(]|[)]|[{]|}|[[]|[]]|[+]|[-]|[\\]|[\*]|[;]|[,]|[=]|[&]|[?]|[.]")

            For Each m As Match In collect
                displayText.SelectionStart = m.Index
                displayText.SelectionLength = m.Length
                If Not (displayText.SelectionColor = Color.Red) Then
                    displayText.SelectionColor = Color.Red

                End If

            Next

            'Preprocesare
            collect = Regex.Matches(displayText.Text, "[#][ -~]*")

            For Each m As Match In collect
                displayText.SelectionStart = m.Index
                displayText.SelectionLength = m.Length
                If Not (displayText.SelectionColor = Color.Green) Then
                    displayText.SelectionColor = Color.Green

                End If

            Next

            'Ghilimele.
            collect = Regex.Matches(displayText.Text, "[\x22][ -~]*[\x22]")
            For Each m As Match In collect
                displayText.SelectionStart = m.Index
                displayText.SelectionLength = m.Length
                If Not (displayText.SelectionColor = Color.Blue) Then
                    displayText.SelectionColor = Color.Blue

                End If

            Next

            'Comentarii
            collect = Regex.Matches(displayText.Text, "[/][/][ -~]*")
            For Each m As Match In collect
                displayText.SelectionStart = m.Index
                displayText.SelectionLength = m.Length
                If Not (displayText.SelectionColor = Color.Gray) Then
                    displayText.SelectionColor = Color.Gray

                End If

            Next

            'Comentarii.
            collect = Regex.Matches(displayText.Text, "(/\*)[ -~\n]*(\*/)")
            For Each m As Match In collect
                displayText.SelectionStart = m.Index
                displayText.SelectionLength = m.Length
                If Not (displayText.SelectionColor = Color.Gray) Then
                    displayText.SelectionColor = Color.Gray

                End If

            Next


        End If

        'Dupa parcurgearea intregului text, revenim cu scrisul live culoarea originala.
        displayText.SelectionStart = originalSelectionStart
        displayText.SelectionLength = originalSelectionLength
        displayText.SelectionColor = originalColor
        displayText.Focus()
    End Sub



    Private Sub SearchAllToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SearchAllToolStripMenuItem.Click
        Dim collect As MatchCollection
        collect = Regex.Matches(displayText.Text, displayText.SelectedText)

        If collect.Count > 0 Then
            SearchForm.searchText.Text = displayText.SelectedText
        End If

        displayText.SelectAll()
        displayText.SelectionBackColor = Color.White

        For Each m As Match In collect

            displayText.Select(m.Index, m.Length)
            displayText.SelectionBackColor = Color.Yellow

        Next
    End Sub

End Class
