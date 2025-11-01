# 🧠 Plagiarism Checker Using KMP  

**Course:** CSE246 – Algorithms  
**Semester:** Summer 2025  
 
**Created by:**  
- blurrryface12 
- ahmed-mannan  

**Submission Date:** 4th September 2025  

---

## 📋 Project Overview  
This project implements a **plagiarism detection system** that compares two text files to measure their similarity using the **Knuth-Morris-Pratt (KMP)** string-matching algorithm.  
The program processes text, divides it into smaller overlapping chunks, and checks for matches between files to calculate a **plagiarism percentage**.

---

## ⚙️ System Requirements  
- **Processor:** Intel Core i5-8365U @ 1.60GHz  
- **RAM:** 8 GB  
- **Operating System:** Windows 11 Pro (64-bit)  
- **IDE:** Code::Blocks 20.03  

---

## 🧩 System Design  
1. **Preprocessing:**  
   Removes punctuation and converts all text to lowercase for uniform comparison.  

2. **Chunk Generation:**  
   Splits one file into overlapping word “chunks” based on file size.  

3. **KMP Algorithm:**  
   Uses the KMP string-matching algorithm to efficiently search each chunk in the second file.  

4. **Plagiarism Calculation:**  
   Compares the number of matched chunks with total chunks to compute a similarity percentage.  

---

## 💻 Implementation Highlights  
**Libraries Used:**  
`<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<algorithm>`, `<iomanip>`, `<limits>`  

**Key Functions:**  
- `readFile()` – Cleans and reads file contents.  
- `computeLPS()` & `KMP()` – Core pattern-matching functions.  
- `count_chunks()` & `create_chunks()` – Generate text segments dynamically.  
- `plagiarism_checker()` – Integrates all steps and outputs the final similarity percentage.  

---

## 🧪 Testing  
- Handles incorrect file inputs gracefully.  
- Displays total chunks, matched chunks, and plagiarism percentage with status.  

---

## 🚀 Future Improvements  
- Enhance detection accuracy for **paraphrased** or **semantically similar** text.  
- Develop a **GUI** for better usability.  
- Enable comparison against **multiple source files**.  
- Integrate a **built-in text editor** for file creation and editing.  

---

## 📄 Full Report  
For detailed design, code explanations, and testing results, see the full project report below:  
[View Project Report (PDF)](link-to-your-pdf)

---

### 🏷️ Repository Info  
**Project Title:** Plagiarism Checker Using KMP  
**Course:** CSE246 – Algorithms (Summer 2025)  
**Institution:** East West University  

---
