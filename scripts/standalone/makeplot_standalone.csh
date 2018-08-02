# /bin/csh -f
# # @$-q all
# # @$-o /dev/null
# # @$-e /disk01/usr3/cvson/tmp/neut_output1.err
 cd /home/cvson/nuicise/neut/neut_5.3.2/src/neutsmpl/
# ##CC coherent
root -b -q 'make_histos_standalone_neut540_cc0pi_v3.cc("neutvec_neut_5.3.6_nd5_C_LFGCCQE.root","basicplotsov3_5.3.6_nd5_C_LFGCCQE_cc0pi.root")'
#root -b -q 'make_histos_standalone_neut540_cc0pi_v3.cc("neutvec_neut_5.3.6_nd5_C_GFGCCQE.root","basicplotsov3_5.3.6_nd5_C_GFGCCQE_cc0pi.root")'
#root -b -q 'make_histos_standalone_neut540_cc0pi_v2.cc("neutvec_neut_5.3.6_nd5_C_GFGCCQE.root","basicplotsov2_5.3.6_nd5_C_GFGCCQE_cc0pi.root")'
# #root -b -q 'make_histos_standalone_neut540.cc("neutvec_5.4.0_nd5_C_CCcoh_RS.root","basicplotso_5.4.0_nd5_C_CCcoh_RS.root")'
# #root -b -q 'make_histos_standalone_neut540.cc("neutvec_5.4.0_nd5_C_CCcoh_BS.root","basicplotso_5.4.0_nd5_C_CCcoh_BS.root")'
# #root -b -q 'make_histos_standalone_neut540.cc("neutvec_5.4.0_nd5_C_CCcoh_RS_MDLQE402.root","basicplotso_5.4.0_nd5_C_CCcoh_RS_MDLQE402.root")'
# #root -b -q 'make_histos_standalone_neut540.cc("neutvec_5.4.0_nd5_C_CCcoh_RS_MDLQE02.root","basicplotso_5.4.0_nd5_C_CCcoh_RS_MDLQE02.root")'
# #root -b -q 'make_histos_standalone_neut540.cc("neutvec_5.4.0_nd2_C_CCcoh_RS.root","basicplotso_5.4.0_nd2_C_CCcoh_RS.root")'
# #root -b -q 'make_histos_standalone_neut540.cc("neutvec_5.4.0_nd2_C_CCcoh_BS.root","basicplotso_5.4.0_nd2_C_CCcoh_BS.root")'
#
#
# ##CC1pi
# #root -b -q 'make_histos_standalone_neut540_cc1pi.cc("neutvec_5.4.0_nd5_C_CC1pi_RS.root","basicplotso_5.4.0_nd5_C_CC1pi_RS.root")'
# #root -b -q 'make_histos_standalone_neut540_cc1pi.cc("neutvec_5.4.0_nd5_C_CC1pi_GS.root","basicplotso_5.4.0_nd5_C_CC1pi_GS.root")'
# #root -b -q 'make_histos_standalone_neut540_cc1pi.cc("neutvec_5.4.0_nd5_C_CC1pi_RS_20piless.root","basicplotso_5.4.0_nd5_C_CC1pi_RS_20piless.root")'
#
# ##CCqe
#root -b -q 'make_histos_standalone_neut540_ccqe.cc("neutvec_neut_5.3.6_mbnumu_CH2_LFGCCQE.root","basicplotso_5.3.6_mbnumu_CH2_LFGCCQE.root")'
# root -b -q 'make_histos_standalone_neut540_ccqe.cc("neutvec_neut_5.3.6_nd5_C_SFCCQE_offpauli.root","basicplotso_5.4.0_nd5_C_SFCCQE_offpauli.root")'
# #root -b -q 'make_histos_standalone_neut540_ccqe.cc("neutvec_5.4.0_nd5_C_CCQE_MDLQE2002.root","basicplotso_5.4.0_nd5_C_CCQE_MDLQE2002.root")'
# #root -b -q 'make_histos_standalone_neut540_ccqe.cc("neutvec_5.4.0_nd5_C_CCQE_MDLQE402.root","basicplotso_5.4.0_nd5_C_CCQE_MDLQE402.root")'
# #root -b -q 'make_histos_standalone_neut540_ccqe.cc("neutvec_5.4.0_nd5_C_CCQE_MDLQE02.root","basicplotso_5.4.0_nd5_C_CCQE_MDLQE02.root")'
#
# #root -b -q 'make_histos_standalone_neut540_ccqe.cc("neutvec_5.4.0_nd5_C_CCQE_MDLQE2002_NORESCAT.root","basicplotso_5.4.0_nd5_C_CCQE_MDLQE2002_NORESCAT.root")'
# #root -b -q 'make_histos_standalone_neut540_ccqe.cc("neutvec_5.4.0_nd5_C_CCQE_MDLQE402_NORESCAT.root","basicplotso_5.4.0_nd5_C_CCQE_MDLQE402_NORESCAT.root")'
# #root -b -q 'make_histos_standalone_neut540_ccqe.cc("neutvec_5.4.0_nd5_C_CCQE_MDLQE02_NORESCAT.root","basicplotso_5.4.0_nd5_C_CCQE_MDLQE02_NORESCAT.root")'
# ##CC0pi
# #root -b -q 'make_histos_standalone_neut540_cc0pi.cc("neutvec_5.4.0_nd5_C_CC0pi_MDLQE2002.root","basicplotso_5.4.0_nd5_C_CC0pi_MDLQE2002.root")'
# #root -b -q 'make_histos_standalone_neut540_cc0pi.cc("neutvec_5.4.0_nd5_C_CC0pi_MDLQE402.root","basicplotso_5.4.0_nd5_C_CC0pi_MDLQE402.root")'
# #root -b -q 'make_histos_standalone_neut540_cc0pi.cc("neutvec_5.4.0_nd5_C_CC0pi_MDLQE02.root","basicplotso_5.4.0_nd5_C_CC0pi_MDLQE02.root")'
#
# ##Global fermi gas
# #root -b -q 'make_histos_standalone_neut540_cc0pi.cc("neutvec_neut_5.3.6_nd5_C_GFGCCQE.root","basicplotso_5.3.6_nd5_C_GFGCCQE_cc0pi.root")'
# #root -b -q 'make_histos_standalone_neut540_cc0pi.cc("neutvec_neut_5.3.6_nd5_C_SFCCQE.root","basicplotso_5.3.6_nd5_C_SFCCQE_cc0pi.root")'
#
# ##all then breakdown
# #root -b -q 'make_histos_standalone_neut540_cc0pi.cc("neutvec_neut_5.3.6_nd5_C_GFGCCQE.root","basicplotso_5.3.6_nd5_C_GFGCCQE_cc0pi.root")'
# #root -b -q 'make_histos_standalone_neut540_cc0pi.cc("neutvec_neut_5.3.6_nd5_C_SFCCQE.root","basicplotso_5.3.6_nd5_C_SFCCQE_cc0pi.root")'
# #root -b -q 'make_histos_standalone_neut540_cc1pi.cc("neutvec_neut_5.3.6_nd5_C_GFGCCQE.root","basicplotso_5.3.6_nd5_C_GFGCCQE_cc1pi.root")'
# #root -b -q 'make_histos_standalone_neut540_cc1pi.cc("neutvec_neut_5.3.6_nd5_C_SFCCQE.root","basicplotso_5.3.6_nd5_C_SFCCQE_cc1pi.root")'
# #root -b -q 'make_histos_standalone_neut540.cc("neutvec_neut_5.3.6_nd5_C_GFGCCQE.root","basicplotso_5.3.6_nd5_C_GFGCCQE_cccoh.root")'
# #root -b -q 'make_histos_standalone_neut540.cc("neutvec_neut_5.3.6_nd5_C_SFCCQE.root","basicplotso_5.3.6_nd5_C_SFCCQE_cccoh.root")'
# #root -b -q 'make_histos_standalone_neut540_ccnpi.cc("neutvec_neut_5.3.6_nd5_C_GFGCCQE.root","basicplotso_5.3.6_nd5_C_GFGCCQE_ccnpi.root")'
# #root -b -q 'make_histos_standalone_neut540_ccnpi.cc("neutvec_neut_5.3.6_nd5_C_SFCCQE.root","basicplotso_5.3.6_nd5_C_SFCCQE_ccnpi.root")'

