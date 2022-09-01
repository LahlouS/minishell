<<OEF infile | cat | cat >> outfile

{
  "type": "Script",
  "commands":
  [
    {
      "type": "Pipeline",
      "commands":
	  [
        {
          "type": "Command",
          "name":
		  {
            "text": "infile",
            "type": "Word"
          },
          "prefix":
		  [
            {
              "text": "<<",
              "type": "dless"
            }
          ]
        },

        {
          "type": "Command",
          "name": {
            "text": "cat",
            "type": "Word"
          }
        },

        {
          "type": "Command",
          "name":
		  {
            "text": "cat",
            "type": "Word"
          },
          "suffix":
		  [
            {
              "type": "Redirect",
              "op":
			  {
                "text": ">>",
                "type": "dgreat"
              },
              "file":
			  {
                "text": "outfile",
                "type": "Word"
              }
            }
          ]
        }

      ]
    }
  ]
}
