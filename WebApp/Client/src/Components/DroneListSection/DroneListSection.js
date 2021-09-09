import React from 'react';
import Accordion from '@material-ui/core/Accordion';
import AccordionSummary from '@material-ui/core/AccordionSummary';
import AccordionDetails from '@material-ui/core/AccordionDetails';
import Typography from '@material-ui/core/Typography';
import ExpandMoreIcon from '@material-ui/icons/ExpandMore';
import DroneListTable from '../DroneListTable/DroneListTable';
import Container from '@material-ui/core/Container';


export default function DroneListSection(props) {
  const [expanded, setExpanded] = React.useState('droneListPanel');

  const handleChange = (panel) => (event, newExpanded) => {
    setExpanded(newExpanded ? panel : false);
  };

  return (
    <div>
      <Accordion square expanded={expanded === 'droneListPanel'} onChange={handleChange('droneListPanel')}>
        <AccordionSummary expandIcon={<ExpandMoreIcon />}>
          <Typography>Drone List</Typography>
        </AccordionSummary>
        <AccordionDetails>
            <Container>
              <DroneListTable dronesData={props.dronesData} />
            </Container>
        </AccordionDetails>
      </Accordion>
    </div>
  );
}