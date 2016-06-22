
TestOrfanidisBiquad
-------------------

### Audio plugin performing peaking EQ with decramped frequency response at Nyquist as per Orfanidis 1997.

![TestOrfanidisBiquad image](http://www.johnflynn.info/images/TestOrfanidisBiquad.png)

Avoids the frequency response distortion of the bilinear transform by assuming the gain at Nyquist is something other than 0 (Robert Bristow Johnson always had set this at 0). Still only uses a biquad, here implemented in direct form I for simplicity and stability.

![TestOrfanidisBiquad frequency response image](http://www.johnflynn.info/images/TestOrfanidisResponse.png)

The image shows high frequency behaviour more closely matches an analogue filter, allowing more 'air' into the sound than standard BLT biquad design (shown here as lighter trace).

See [www.johnflynn.info](http://www.johnflynn.info/)
