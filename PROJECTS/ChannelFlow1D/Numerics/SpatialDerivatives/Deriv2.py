def deriv2(
    inputs_AD = {'uL':[], 'uC':[], 'uR':[]},
    inputs    = {'yL':[], 'yC':[], 'yR':[]}
):

    leftDeriv = (inputs_AD['uC']-inputs_AD['uL']) / \
                (inputs['yC']-inputs['yL'])
    
    rightDeriv = (inputs_AD['uR']-inputs_AD['uC']) / \
                 (inputs['yR']-inputs['yC'])
    
    d2udy2 = 2 * (rightDeriv-leftDeriv) / (inputs['yR']-inputs['yL'])

    outputs = { }
    outputs_AD = { 'd2udy2' : d2udy2 }

    return outputs, outputs_AD