# SLAM
Simultaneous Localization And Mapping

Projet de fin d'étude, Supélec Majeure SERI.


[TEST�]

codeur: Gestion de l'interruption des codeurs seuls

client_Timer: (fonctionne avec server_Timer)
		Reception de l'heure
	
server_Timer: (fonctionne avec client_Timer)
		Envoi de l'heure toute les secondes par Timer_interrupt
[PAS TEST�]

codeur_timer: Gestion des codeurs via un interrupt_timer 
			
codeur_timer_client: Gestion de l'envoi des valeurs codeurs via le Timer_interrupt + r�ception PWM 

