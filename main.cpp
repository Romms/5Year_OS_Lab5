#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>


bool isConsonant(char const &c) {
   return
         (
              c=='a'
           || c=='e'
           || c=='i'
           || c=='o'
           || c=='u'
         )
         ||
         (
              c=='A'
           || c=='E'
           || c=='I'
           || c=='O'
           || c=='U'
         );
}

int consonantsCount(std::string const &str) {
   int count;
   for (char c : str) {
      if (isConsonant(c))
         count++;
   }

   return count;
}

bool compare_words(std::string first, std::string second){
   return consonantsCount(first) > consonantsCount(second);
}


int main() {

   const size_t BUFFERSIZE = 1000;
   const size_t BUFFERBYTESIZE = sizeof (char);
   FILE * pFile;
   char * buffer;
   size_t result;

   std::vector<std::string> words;
   std::string word = "";
   char c;

   pFile = fopen ( "/tmp/1.txt" , "rb" );
   if (pFile==NULL) {
      fputs ("File error",stderr);
      exit (1);
   }

   // allocate memory for the buffer:
   buffer = (char*) malloc (sizeof(char) * BUFFERSIZE);
   if (buffer == NULL) {
      fputs ("Memory error",stderr);
      exit (2);
   }


   while(result = fread(buffer, BUFFERBYTESIZE, BUFFERSIZE, pFile)) {
      for(int i = 0; i < result; i++){
         c = buffer[i];
         if(isalpha(c)) {
            word += c;
         } else {
            if(!word.empty()){
               words.push_back(word);
               word = "";
            }
         }
      }

      if(!word.empty()){
         words.push_back(word);
         word = "";
      }
   }


   sort(words.begin(), words.end(), compare_words);

   // terminate
   fclose (pFile);
   free (buffer);

   for(std::string str : words){
      puts (str.c_str());
   }

   return 0;
}
