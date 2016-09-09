# CS265_Project01
Project 01 for SJSU CS265 Cryptography and Computer Security

The precise details of your project will vary somewhat depending on the challenge you select, but, in general, you will be expected to do all of the following:
- Study your selected cryptosystem
- Write software to implement the system
- Write software to implement the attack on the system
- Estimate the work factor for your attack
- Conduct computational experiments to verify your analysis
- Ideally, you will provide a complete solution for your selected challenge
problem
- Write a report that includes a detailed description and analysis of your
work and results

In summary, you must become an expert on the system that you choose to attack, and your work must demonstrate your newfound expertise.

- You are expected to work with a partner. All projects will be ranked against all other projects.  
- You must select your project topic by the date given in the course syllabus. Instructor approval of your topic is required. This must be done via email. The topics are first come, first served. For your email, use subject line "CS265-01 Cryptanalysis Topic" or "CS265-02 Cryptanalysis Topic" as appropriate. Send your email to auston.davis@sjsu.edu . If I have any concerns regarding your selected topic, I will let you know promptly. It is to your advantage to spend some effort to initially select a good topic.  
- All software must be written in C (if you do not know C, the language must be approved by me). In most cases, the number of lines of code will be relatively small, but the coding may be technical and challenging.  
- You must write a report that includes a detailed description and analysis of your work and results. There is no minimum or maximum length for this paper, but quality is far more important than quantity. Your paper should be concise and to the point. Your grade for the project will be largely determined by the content and substance of your paper. While this is not a writing class, poor grammar, usage, organization, etc., will definitely not help your cause and may detract significantly from your grade. Every page of your report must include the authors' names and email addresses.  
- Papers may be submitted to www.turnitin.com, an online plagiarism detection tool. If the instructor determines that you have committed plagiarism, you will fail the course and an academic dishonesty report will be submitted. The official SJSU policy on academic dishonesty (including plagiarism) can be found at http://www2.sjsu.edu/senate/s98-1.htm.  
- On or before the due date, submit all material (including source code), put all info in a single zip file named Lastname1_Lastname2.zip, where Lastname1 and Lastname2 are the last names of you and your partner. The subject line of the email must read "CS265-01 Cryptanalysis Project" or "CS265-02 Cryptanalysis Project", as appropriate. You will upload your final project to Canvas under the assignment section titled “Cryptography Poject”  
- Finally, it is imperative that you begin working on this project immediately and that you work on it consistently. This is not the type of project that can be completed in a few days, no matter how many hours you work each day. It is also not the kind of project that you can drop and easily pick up where you left off. These are highly technical and challenging problems that require constant and ongoing effort to make any real progress.

#HANDYCIPHER – PART 1#

Author: Bruce Kallick

January 2015

##Introduction##
Handycipher is a low-tech stream cipher, simple enough to permit pen-and-paper encrypting and decrypting of messages, while providing a significantly high level of security. Handycipher was published and further improved in 2014.  
Handycipher consists of a core cipher augmented by a random interspersing of null characters throughout the ciphertext as decoys intended to thwart attacks based on recognizing patterns in the ciphertext.  
The core cipher incorporates two ciphers based on the same key: a simple substitution cipher and a nondeterministic homophonic substitution cipher.

##Challenge##
Part 1 of the Handycipher series is a partly-known plaintext challenge. How Handycipher works is described in detail in the extra pdf within the additional zip file.  
Your task is to recover some of the 858-character plaintext message M, given the 3,679-character ciphertext C generated by encrypting M with Handycipher and the secret key K. (For a full break, try also to discover K.)  
The ciphertext C is given as a text file within the additional zip file. You are also given there another text file containing the first 229 letters of the plaintext M.  
The solution consists of the first five words of the second-to-last sentence of M. Please enter the solution with spaces.

##References##
In the document "MTC3_Handycipher_Description.pdf" the cipher is explained in detail. You can find it within the additional zip file.

Another detailed explanation can be found at http://eprint.iacr.org/2014/257.pdf  
Remark: The eprint paper also introduces the Extended Handycipher method (EHC). For the EHC cipher we will offer another series of MTC3 challenges.

Successful cryptanalysis of earlier versions of Handycipher can be found here - however, it's more fun to try by yourself :smile:   
https://oilulio.wordpress.com/2014/06/19/handycipher-decrypt/  
https://oilulio.wordpress.com/2014/07/28/breaking-handycipher-2/

The additional zip archive contains the following files:


- MTC3_Handycipher_Description.pdf  
̄ detailed explanation of Handycipher  
- known-plaintext_HC-01.txt  
̄ the known part of the plaintext  
- ciphertext_HC-01.txt  
̄ the complete ciphertext  
- handycipher.zip  
̄ Python code and test files for Handycipher  